#ifndef PACKET_PARSER_H
#define PACKET_PARSER_H

#include <sys/types.h>


typedef struct {
    int tcp_count;
    int udp_count;
    int icmp_count;
    int other_count;
} packet_stats_t;


void process_packet(const u_char *packet, packet_stats_t *packet_stats);
int get_packet_protocol(const u_char *packet);
void print_stats(const packet_stats_t *stats);


#endif
