#!/usr/bin/env bash
# Create a persistent TUN interface suitable for tun_reader.

set -euo pipefail

if (( EUID != 0 )); then
    echo "Run this script as root, for example: sudo $0" >&2
    exit 1
fi

owner=${1:-${SUDO_USER:-root}}
address=${2:-}

if ! id "$owner" >/dev/null 2>&1; then
    echo "No such user: $owner" >&2
    exit 1
fi

if ip link show dev tun0 >/dev/null 2>&1; then
    echo "tun0 already exists; reusing it"
else
    ip tuntap add dev tun0 mode tun user "$owner"
    echo "created persistent TUN interface tun0 for user $owner"
fi

ip link set dev tun0 up

if [[ -n "$address" ]]; then
    ip address replace "$address" dev tun0
    echo "assigned $address to tun0"
fi

ip -brief address show dev tun0
