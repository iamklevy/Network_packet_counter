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

# RunTime screenshots/logs
**1. pcap on wlan0 interface (-f "tcp")**
<img width="1920" height="1080" alt="wlan0 every 3sec only TCP" src="https://github.com/user-attachments/assets/345ae6cb-bb2a-4712-b44f-b0f8edd3fa8b" />

**2. Verifing correct protocol identification (-f "imcp")**
<img width="1920" height="1080" alt="Screenshot_2025-08-21_01_53_38" src="https://github.com/user-attachments/assets/802313e2-daf8-4a1e-9c10-56f39ef3f812" />

**3. stress test with ping flood**
<img width="1920" height="1080" alt="stress_test2" src="https://github.com/user-attachments/assets/45a645df-e708-477a-b2d4-bb7557352f70" />

**4. Zero packet loss after stress Test**
<img width="1920" height="1080" alt="stress_test1" src="https://github.com/user-attachments/assets/a9a507c9-f1bd-4978-a514-fc4c330de627" />

**5. Memory usage for the program Executable (~4-5 MB)**
<img width="1920" height="1080" alt="mem usage 4 5 MiB" src="https://github.com/user-attachments/assets/16f49596-83b9-452e-bc9c-43e8c3ec285a" />

**6.Testing eth0 interface on Raspberrypi5**
![RPI5](https://github.com/user-attachments/assets/4ff24d40-bcd5-4516-b388-e197e3e0102b)





