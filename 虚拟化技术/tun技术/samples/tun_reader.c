// SPDX-License-Identifier: MIT
/*
 * Smallest useful TUN example: print IPv4 packets routed to tun0.
 *
 * Build: make
 * Run:   ./tun_reader --iface tun0
 */

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <netinet/ip.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define PACKET_MAX 65535

static int open_tun(char *name)
{
    struct ifreq ifr;
    int fd;

    fd = open("/dev/net/tun", O_RDWR | O_CLOEXEC);
    if (fd < 0) {
        perror("open /dev/net/tun");
        return -1;
    }

    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
    snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%s", name);

    if (ioctl(fd, TUNSETIFF, &ifr) < 0) {
        perror("ioctl TUNSETIFF");
        close(fd);
        return -1;
    }

    snprintf(name, IFNAMSIZ, "%s", ifr.ifr_name);
    return fd;
}

static void print_packet(const uint8_t *packet, size_t len)
{
    struct in_addr source;
    struct in_addr destination;
    char source_text[INET_ADDRSTRLEN];
    char destination_text[INET_ADDRSTRLEN];
    const struct iphdr *ip;

    if (len < 1) {
        puts("received an empty packet");
        return;
    }

    if (packet[0] >> 4 != 4 || len < sizeof(*ip)) {
        printf("received %zu-byte non-IPv4 packet\n", len);
        return;
    }

    ip = (const struct iphdr *)packet;
    if (ip->ihl < 5 || len < (size_t)ip->ihl * 4) {
        printf("received malformed IPv4 packet (%zu bytes)\n", len);
        return;
    }

    source.s_addr = ip->saddr;
    destination.s_addr = ip->daddr;
    inet_ntop(AF_INET, &source, source_text, sizeof(source_text));
    inet_ntop(AF_INET, &destination, destination_text, sizeof(destination_text));

    printf("IPv4: %s -> %s, protocol %u, %zu bytes\n",
           source_text, destination_text, ip->protocol, len);
}

static void usage(const char *program)
{
    fprintf(stderr, "Usage: %s [--iface NAME]\n", program);
}

int main(int argc, char **argv)
{
    char ifname[IFNAMSIZ] = "tun0";
    uint8_t *packet;
    int fd;
    int i;

    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--iface") && i + 1 < argc) {
            snprintf(ifname, sizeof(ifname), "%s", argv[++i]);
        } else {
            usage(argv[0]);
            return EXIT_FAILURE;
        }
    }

    fd = open_tun(ifname);
    if (fd < 0)
        return EXIT_FAILURE;

    packet = malloc(PACKET_MAX);
    if (!packet) {
        perror("malloc");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("attached to %s; reading IP packets (Ctrl-C to stop)\n", ifname);
    for (;;) {
        ssize_t len = read(fd, packet, PACKET_MAX);

        if (len < 0) {
            if (errno == EINTR)
                continue;
            perror("read TUN");
            free(packet);
            close(fd);
            return EXIT_FAILURE;
        }
        print_packet(packet, (size_t)len);
    }
}
