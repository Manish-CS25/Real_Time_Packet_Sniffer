#include "packet_sniffer.h"
#include "logger.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <linux/if_ether.h>
#include <unistd.h>

#define BUFFER_SIZE 2048
static unsigned char buffer[BUFFER_SIZE];  // Static buffer for reuse


void start_packet_sniffer() {
    int raw_socket;
    unsigned char *buffer = (unsigned char *)malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        perror("Failed to allocate buffer");
        exit(1);
    }

    // Create the raw socket
    raw_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (raw_socket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Capture packets continuously
    while (1) {
        ssize_t packet_size = recvfrom(raw_socket, buffer, BUFFER_SIZE, 0, NULL, NULL);
        if (packet_size < 0) {
            perror("Failed to capture packet");
            break;
        }

        printf("Packet captured! Size: %ld bytes\n", packet_size);

        // Process the captured packet
        process_ip_packet(buffer, packet_size);
    }

    close(raw_socket);
    free(buffer);
}

void process_ip_packet(unsigned char *buffer, ssize_t size) {
    struct iphdr *ip_header = (struct iphdr *)(buffer + sizeof(struct ethhdr));

    struct sockaddr_in src, dest;
    src.sin_addr.s_addr = ip_header->saddr;
    dest.sin_addr.s_addr = ip_header->daddr;

    char src_ip[INET_ADDRSTRLEN];
    char dest_ip[INET_ADDRSTRLEN];
    strcpy(src_ip, convert_ip_address(src.sin_addr.s_addr));
    strcpy(dest_ip, convert_ip_address(dest.sin_addr.s_addr));

    printf("Source IP: %s, Destination IP: %s, Protocol: %d\n", src_ip, dest_ip, ip_header->protocol);

    // Assign priority based on protocol
    if (ip_header->protocol == 1) {
        printf("High Priority: ICMP packet\n");
        // Handle ICMP packets immediately
    } else if (ip_header->protocol == 6) {
        printf("Medium Priority: TCP packet\n");
        // Queue TCP packets for later processing
    } else if (ip_header->protocol == 17) {
        printf("Low Priority: UDP packet\n");
        // Process UDP packets later
    }

    // Log the packet
    char log_message[256];
    sprintf(log_message, "Source IP: %s, Destination IP: %s, Protocol: %d\n",
            src_ip, dest_ip, ip_header->protocol);
    log_packet_info(log_message);
}

