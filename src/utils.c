#include "utils.h"
#include <arpa/inet.h>
#include <stdio.h>

char *convert_ip_address(unsigned long ip_addr) {
    struct in_addr ip;
    ip.s_addr = ip_addr;
    return inet_ntoa(ip);
}