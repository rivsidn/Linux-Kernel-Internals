#!/usr/bin/env bash
# Create a persistent TAP interface suitable for tap_demo.

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

if ip link show dev tap0 >/dev/null 2>&1; then
    echo "tap0 already exists; reusing it"
else
    ip tuntap add dev tap0 mode tap user "$owner"
    echo "created persistent TAP interface tap0 for user $owner"
fi

ip link set dev tap0 up

if [[ -n "$address" ]]; then
    ip address replace "$address" dev tap0
    echo "assigned $address to tap0"
fi

ip -brief address show dev tap0
