Real-Time Packet Sniffer
Overview

The Real-Time Packet Sniffer is a C-based application that captures and analyzes network packets in real-time. It operates using raw sockets, processes each packet, and logs important information such as IP addresses, protocols, and payload sizes. This project is designed to provide insight into low-level network traffic.
Features:

    Capture packets from any network interface.
    Process IP packets and log details.
    Store captured data in a log file.
    Modular structure for easy extension and testing.

Directory Structure

bash

real_time_packet_sniffer/
├── include/
│   ├── packet_sniffer.h        # Header for packet processing
│   ├── logger.h                # Header for logging
│   └── utils.h                 # Utility functions
├── src/
│   ├── packet_sniffer.c        # Core packet capture and processing logic
│   ├── logger.c                # Logging functionality
│   ├── utils.c                 # Utility functions
│   └── main.c                  # Main file to run the sniffer
├── logs/
│   └── packet_log.txt          # Log file (generated after the first run)
├── test/
│   ├── test_packet_sniffer.c   # Tests for packet sniffer
│   └── test_logger.c           # Tests for logger
├── README.md                   # Project documentation
└── LICENSE                     # License file (Optional)

How to Compile and Run
Prerequisites

    Linux-based environment (for raw socket usage).
    GCC (GNU Compiler Collection).
    Root privileges for running raw socket operations.

Compilation

If you are not using a Makefile, follow these steps to manually compile the project:

    Navigate to the project directory:

    bash

cd real_time_packet_sniffer

Compile each source file:

bash

gcc -c src/packet_sniffer.c -Iinclude
gcc -c src/logger.c -Iinclude
gcc -c src/utils.c -Iinclude
gcc -c src/main.c -Iinclude

Link the object files to create the executable:

bash

    gcc -o packet_sniffer main.o packet_sniffer.o logger.o utils.o

Running the Program

Since the program uses raw sockets, it needs to be run with root privileges:

bash

sudo ./packet_sniffer

Once the sniffer is running, it will capture packets in real-time and log the details to logs/packet_log.txt.
Viewing Logs

You can view the captured packet details by reading the log file:

bash

cat logs/packet_log.txt

Testing

The project includes basic unit tests for the packet sniffer and logger.
Running Tests

    Compile and run test_packet_sniffer.c:

    bash

gcc -o test_sniffer test/test_packet_sniffer.c packet_sniffer.o logger.o utils.o -Iinclude
sudo ./test_sniffer

Compile and run test_logger.c:

bash

    gcc -o test_logger test/test_logger.c logger.o -Iinclude
    ./test_logger

These tests will verify the functionality of your packet sniffer and logging components.