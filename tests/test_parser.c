#include "../include/packet_parser.h"
#include "../src/packet_parser.c"
#include <stdio.h>

// Dummy test (you can expand with crafted packet data)
int main() {
    packet_stats_t stats = {4,0,0,0};

    // Fake empty packet (not real)
    unsigned char fake_packet[64] = {0};

    process_packet(fake_packet, &stats);

    printf("After processing fake packet:\n");
    print_stats(&stats);

    return 0;
}
