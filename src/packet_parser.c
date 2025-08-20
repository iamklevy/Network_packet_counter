#include "../include/packet_parser.h"
#include <stdio.h>
#include <time.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <net/ethernet.h>

int get_packet_protocol(const u_char *packet) {
    const struct ether_header *ether_header = (struct ether_header *)packet;

    // Only handle IPV4 packets
    if (ntohs(ether_header->ether_type) != ETHERTYPE_IP) {
        return 0; // Other
    }

    //packets starts with an Ethernet header,  Move past it to reach IP header.
    const struct ip *ip_header = (struct ip *)(packet + sizeof(struct ether_header));


    switch (ip_header->ip_p) {
        case IPPROTO_TCP: return IPPROTO_TCP;
        case IPPROTO_UDP: return IPPROTO_UDP;
        case IPPROTO_ICMP: return IPPROTO_ICMP;
        default: return 0; //other protocols

    }

}

void process_packet(const u_char *packet, packet_stats_t *packet_stats) {
    const int protocol = get_packet_protocol(packet);

    switch (protocol) {
        case IPPROTO_TCP: packet_stats->tcp_count++;
        case IPPROTO_UDP: packet_stats->udp_count++;
        case IPPROTO_ICMP: packet_stats->icmp_count++;
        default: packet_stats->other_count++;
    }
}

void print_stats(const packet_stats_t *stats) {

    time_t now;
    char buffer[64];

    time(&now);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
    printf("\n-**- Packet Statistics -**-[%s]\n", buffer);
    printf("TCP:   %d\n", stats->tcp_count);
    printf("UDP:   %d\n", stats->udp_count);
    printf("ICMP:  %d\n", stats->icmp_count);
    printf("Other: %d\n", stats->other_count);
    printf("--------------------------\n");
}