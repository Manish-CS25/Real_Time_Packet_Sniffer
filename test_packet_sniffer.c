#include <stdio.h>
#include <string.h>
#include "../include/packet_sniffer.h"
#include "../include/logger.h"
#include "../include/utils.h"

// Mock buffer to simulate network packet data
unsigned char mock_packet[65536];

// Mock the IP and Ethernet headers in the buffer
void mock_ip_packet() {
    // Clear the buffer
    memset(mock_packet, 0, sizeof(mock_packet));

    // Fill Ethernet header (we skip this in test, just mock)
    // Fill IP header (pretend it's IPv4 with source and dest)
    struct iphdr *ip_header = (struct iphdr *)(mock_packet + sizeof(struct ethhdr));
    ip_header->saddr = inet_addr("192.168.0.1");
    ip_header->daddr = inet_addr("192.168.0.2");
    ip_header->protocol = 1; // ICMP protocol (for testing priority)
}

// Test case to process a mock packet
void test_process_ip_packet() {
    mock_ip_packet();

    // Test the processing of the mock packet
    process_ip_packet(mock_packet, sizeof(mock_packet));
    printf("Packet processed successfully\n");
}

int main() {
    printf("Starting Packet Sniffer Tests...\n");

    // Run the test
    test_process_ip_packet();

    return 0;
}
