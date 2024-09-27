#include "logger.h"
#include <stdio.h>

void log_packet_info(const char *info) {
    FILE *logfile = fopen("logs/packet_log.txt", "a");
    if (logfile == NULL) {
        perror("Failed to open log file");
        return;
    }
    fprintf(logfile, "%s", info);
    fclose(logfile);
}

