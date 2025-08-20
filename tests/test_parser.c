#include "../include/packet_parser.h"
#include "../src/packet_parser.c"
#include <stdio.h>
#include <string.h>
#include <assert.h>

// Helper function to create fake Ethernet + IP packet   (Generated with Chat GPT5)
void create_fake_ip_packet(u_char *packet, int protocol) {
    memset(packet, 0, 64);

    // Ethernet header (14 bytes)
    packet[12] = 0x08;  // Ethernet type: IPv4 (0x0800)
    packet[13] = 0x00;

    // IP header (start at offset 14)
    packet[14] = 0x45; // Version & IHL
    packet[23] = (u_char)protocol; // Protocol field
}

int main() {
    packet_stats_t stats = {0, 0, 0, 0};
    u_char packet[64];

    // Test TCP
    create_fake_ip_packet(packet, IPPROTO_TCP);
    process_packet(packet, &stats);
    assert(stats.tcp_count == 1);
    assert(stats.udp_count == 0);
    assert(stats.icmp_count == 0);
    assert(stats.other_count == 0);

    // Test UDP
    create_fake_ip_packet(packet, IPPROTO_UDP);
    process_packet(packet, &stats);
    assert(stats.tcp_count == 1);
    assert(stats.udp_count == 1);
    assert(stats.icmp_count == 0);
    assert(stats.other_count == 0);

    // Test ICMP
    create_fake_ip_packet(packet, IPPROTO_ICMP);
    process_packet(packet, &stats);
    assert(stats.tcp_count == 1);
    assert(stats.udp_count == 1);
    assert(stats.icmp_count == 1);
    assert(stats.other_count == 0);

    // Test Other protocol
    create_fake_ip_packet(packet, 0x99); // unknown protocol
    process_packet(packet, &stats);
    assert(stats.tcp_count == 1);
    assert(stats.udp_count == 1);
    assert(stats.icmp_count == 1);
    assert(stats.other_count == 1);

    printf("All unit tests passed!\n");
    print_stats(&stats);

    return 0;
}
