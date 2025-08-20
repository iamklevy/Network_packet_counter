#include "../include/packet_parser.h"
#include "../src//packet_parser.c"
#include <stdio.h>



//Expected output (since fake packet is not a real IP packet, it counts as “Other”):
int main() {
    // Initialize stats
    packet_stats_t stats = {0, 0, 0, 0};

    // fake packet (content doesn't matter here)
    unsigned char fake_packet[64] = {0};

    // Process the packet
    process_packet(fake_packet, &stats);

    // Print the updated stats
    print_stats(&stats);

    return 0;
}
