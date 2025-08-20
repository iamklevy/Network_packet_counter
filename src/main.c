#include "../include/packet_parser.h"
#include <pcap.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

static packet_stats_t stats;
static pcap_t *handle = NULL;
static int interval = 5; //default interval; stats every 5 seconds.

void handle_sigint(const int sig) {
    (void)sig;
    printf("\nStopping capture...\n");
    if (handle) pcap_breakloop(handle);
}

void packet_handler(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
    (void)h;
    packet_stats_t *stats = (packet_stats_t*)user;
    process_packet(bytes, stats);
}

int main(const int argc, char *argv[]) {
    char *interface = NULL;
    char error_buf[PCAP_ERRBUF_SIZE];
    char *filter_exp = NULL;
    struct bpf_program fp;
    bpf_u_int32 mask, net;

    // Parse args: -i <interface> [-f filter] [-t seconds]
    int opt;
    while ((opt = getopt(argc, argv, "i:f:t:")) != -1) {
        switch (opt) {
            case 'i': interface = optarg; break;
            case 'f': filter_exp = optarg; break;
            case 't': interval = atoi(optarg); break;
            default:
                fprintf(stderr, "Usage: %s -i <interface> [-f filter] [-t seconds]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (!interface) {
        fprintf(stderr, "No interface specified.\n");
        exit(EXIT_FAILURE);
    }

    // Get network mask and addr
    if (pcap_lookupnet(interface, &net, &mask, error_buf) == -1) {
        fprintf(stderr, "Could not get netmask for %s: %s\n", interface, error_buf);
        net = 0;
        mask = 0;
    }

    // Open interface communication
    handle = pcap_open_live(interface, BUFSIZ, 1, 1000, error_buf);
    if (!handle) {
        fprintf(stderr, "Couldn't open Network Interface %s: %s\n", interface, error_buf);
        return 2;
    }

    // Apply filter if provided
    if (filter_exp) {
        if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
            fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
            return 2;
        }
        if (pcap_setfilter(handle, &fp) == -1) {
            fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(handle));
            return 2;
        }
    }

    // Handle CTRL+C
    signal(SIGINT, handle_sigint);

    // Capture loop
    time_t last_time = time(NULL);
    while (1) {
        const int rc = pcap_dispatch(handle, -1, packet_handler, (u_char*)&stats);
        if (rc == -2) break;
        if (rc == -1) {
            fprintf(stderr, "pcap_dispatch failed: %s\n", pcap_geterr(handle));
            break;
        }
        if (difftime(time(NULL), last_time) >= interval) {
            print_stats(&stats);
            last_time = time(NULL);
        }
    }

    pcap_close(handle);
    return 0;
}