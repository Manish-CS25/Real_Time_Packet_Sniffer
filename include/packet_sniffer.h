#ifndef PACKET_SNIFFER_H
#define PACKET_SNIFFER_H


#include <sys/types.h>
void start_packet_sniffer();
void process_ip_packet(unsigned char *buffer, ssize_t size);

#endif