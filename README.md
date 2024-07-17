# Raw-Packet-Capture-Program
This repository contains a simple C program that creates a raw socket to capture and display network packets at the data link layer (Layer 2). It can identify and print details about IP and ARP packets, as well as display the type of packet (outgoing, broadcast, multicast, or incoming).

## Overview
This program creates a raw socket using the PF_PACKET domain and SOCK_RAW type to capture all Ethernet frames passing through the network interface. It then decodes and displays basic information about the captured packets.

## Features

+ Creates a raw socket to capture all Ethernet frames.

+ Identifies and prints details about IP and ARP packets.

+ Displays packet type (outgoing, broadcast, multicast, or incoming).

+ Prints raw packet data in hexadecimal format.

## Requirements

* Linux operating system.

* C compiler (e.g., gcc).

* Root or superuser privileges (required for creating raw sockets).

## Building the Code
You can use the provided Makefile to build the program.

**1-** Open a terminal.

**2-** Navigate to the directory containing the Makefile.

**3-** Run the following command to build the program :

```bash
make
```
## Usage
To run the program, execute the following command with root privileges:

``` bash
sudo ./packet_capture
```
The program will start capturing packets and printing their details to the console. Press Ctrl+C to stop the program.
