# Network Packet Counter

A lightweight C program that captures and counts network packets on a live interface using **libpcap**, classifying them into TCP, UDP, ICMP, and other protocols. Includes periodic statistics with timestamps.

## Features

* Capture live network traffic on a real interface.
* Count TCP, UDP, ICMP, and other packets.
* Display packet statistics every configurable interval (default: 5 seconds).
* Apply BPF filters to capture specific protocols or traffic.

## Build Instructions

**Prerequisites:**

* GCC (or Clang)
* libpcap development library
* CMake (optional if using the provided CMakeLists.txt)

**Using GCC:**

```bash
gcc src/main.c src/packet_parser.c -o packet_counter -lpcap
```

**Using CMake:**

```bash
mkdir build
cd build
cmake ..
make
```

## Run Instructions

```bash
sudo ./packet_counter -i <interface> [-f <filter>] [-t <seconds>]
```

**Options:**

* `-i <interface>` : Network interface to capture packets (e.g., wlan0, eth0)
* `-f <filter>`    : Optional BPF filter (e.g., "tcp", "udp", "icmp")
* `-t <seconds>`   : Optional interval for printing stats (default: 5)

**Example:**

```bash
sudo ./packet_counter -i wlan0 -f "tcp" -t 10
```

Prints TCP packet counts every 10 seconds.

**Give the executable the root capabilities (so you don’t need sudo):**
```bash
sudo setcap cap_net_raw,cap_net_admin=eip ./packet_counter
```


## Notes

* Requires root privileges or `CAP_NET_RAW` capability to capture packets.
* Works on Linux with actual network interfaces.
* Designed to handle at least 1000 packets/sec with memory usage under 10MB.


