// SPDX-License-Identifier: MIT
/*
 * Minimal TAP demonstration.
 *
 *   sudo ./tap_demo --iface tap0
 *   sudo ./tap_demo --iface tap0 --inject-arp 192.168.100.2
 *
 * The normal mode reads Ethernet frames that Linux sends through the TAP
 * interface.  --inject-arp writes an Ethernet/ARP frame to the TAP file
 * descriptor, which injects it into Linux as a frame received on tap0.
 */

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <netinet/if_ether.h>
#include <net/if_arp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define FRAME_MAX 2048

static int open_tap(char *name)
{
    struct ifreq ifr;
    int fd;

    fd = open("/dev/net/tun", O_RDWR | O_CLOEXEC);
    if (fd < 0) {
        perror("open /dev/net/tun");
        return -1;
    }

    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
    snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%s", name);

    if (ioctl(fd, TUNSETIFF, &ifr) < 0) {
        perror("ioctl TUNSETIFF");
        close(fd);
        return -1;
    }

    snprintf(name, IFNAMSIZ, "%s", ifr.ifr_name);
    return fd;
}

static void print_frame(const uint8_t *frame, size_t len)
{
    size_t i;
    size_t shown = len < 64 ? len : 64;

    printf("read %zu bytes: ", len);
    for (i = 0; i < shown; i++)
        printf("%02x%s", frame[i], i + 1 == shown ? "" : " ");
    if (shown < len)
        printf(" ...");
    putchar('\n');
}

static int inject_arp_request(int fd, const char *target_ip)
{
    struct ether_header *eth;
    struct arphdr *arp;
    struct in_addr target;
    uint8_t frame[sizeof(*eth) + sizeof(*arp) + 20];
    uint8_t source_mac[] = { 0x02, 0x00, 0x00, 0x00, 0x00, 0x01 };
    uint8_t *payload;
    ssize_t written;

    if (inet_pton(AF_INET, target_ip, &target) != 1) {
        fprintf(stderr, "invalid IPv4 address: %s\n", target_ip);
        return -1;
    }

    memset(frame, 0, sizeof(frame));
    eth = (struct ether_header *)frame;
    memset(eth->ether_dhost, 0xff, ETH_ALEN);
    memcpy(eth->ether_shost, source_mac, ETH_ALEN);
    eth->ether_type = htons(ETH_P_ARP);

    arp = (struct arphdr *)(frame + sizeof(*eth));
    arp->ar_hrd = htons(ARPHRD_ETHER);
    arp->ar_pro = htons(ETH_P_IP);
    arp->ar_hln = ETH_ALEN;
    arp->ar_pln = 4;
    arp->ar_op = htons(ARPOP_REQUEST);

    payload = (uint8_t *)(arp + 1);
    memcpy(payload, source_mac, ETH_ALEN);       /* sender hardware address */
    memset(payload + ETH_ALEN, 0, 4);            /* sender protocol address */
    memset(payload + ETH_ALEN + 4, 0, ETH_ALEN); /* target hardware address */
    memcpy(payload + 2 * ETH_ALEN + 4, &target, 4);

    written = write(fd, frame, sizeof(frame));
    if (written != (ssize_t)sizeof(frame)) {
        if (written < 0)
            perror("write TAP");
        else
            fprintf(stderr, "short TAP write: %zd bytes\n", written);
        return -1;
    }

    printf("wrote a %zd-byte ARP request into TAP (target %s)\n",
           written, target_ip);
    return 0;
}

static void usage(const char *program)
{
    fprintf(stderr, "Usage: %s [--iface NAME] [--inject-arp IPv4]\n", program);
}

int main(int argc, char **argv)
{
    char ifname[IFNAMSIZ] = "tap0";
    const char *arp_target = NULL;
    uint8_t frame[FRAME_MAX];
    int fd;
    int i;

    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--iface") && i + 1 < argc) {
            strncpy(ifname, argv[++i], IFNAMSIZ - 1);
            ifname[IFNAMSIZ - 1] = '\0';
        } else if (!strcmp(argv[i], "--inject-arp") && i + 1 < argc) {
            arp_target = argv[++i];
        } else {
            usage(argv[0]);
            return EXIT_FAILURE;
        }
    }

    fd = open_tap(ifname);
    if (fd < 0)
        return EXIT_FAILURE;

    printf("attached to %s\n", ifname);
    if (arp_target) {
        int rc = inject_arp_request(fd, arp_target);
        close(fd);
        return rc ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    printf("reading Ethernet frames; press Ctrl-C to stop\n");
    for (;;) {
        ssize_t len = read(fd, frame, sizeof(frame));
        if (len < 0) {
            if (errno == EINTR)
                continue;
            perror("read TAP");
            close(fd);
            return EXIT_FAILURE;
        }
        print_frame(frame, (size_t)len);
    }
}
