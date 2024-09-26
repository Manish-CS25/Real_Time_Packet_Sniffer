#include <stdio.h>
#include <string.h>
#include "../include/logger.h"

// Test function to verify log writing
void test_log_packet_info() {
    const char *test_log = "Test log entry for packet\n";
    log_packet_info(test_log);

    // Open the log file to verify
    FILE *logfile = fopen("logs/packet_log.txt", "r");
    if (logfile == NULL) {
        perror("Failed to open log file");
        return;
    }

    // Read the last line in the log file
    char buffer[256];
    fseek(logfile, -256, SEEK_END);  // Move file pointer to near the end
    fgets(buffer, sizeof(buffer), logfile);

    // Check if the log message matches
    if (strstr(buffer, "Test log entry for packet") != NULL) {
        printf("Logging test passed!\n");
    } else {
        printf("Logging test failed.\n");
    }

    fclose(logfile);
}

int main() {
    printf("Starting Logger Tests...\n");

    // Run the logging test
    test_log_packet_info();

    return 0;
}