---

# Raw Packet Capture Program

## 📋 Overview
This repository contains a simple C program that creates a raw socket to capture and display network packets at the data link layer (Layer 2). It identifies and prints details about IP and ARP packets, while displaying the type of packet (outgoing, broadcast, multicast, or incoming).

---

## 🚀 Features

- **Create Raw Socket:** Captures all Ethernet frames passing through the interface.
- **Packet Identification:** Detects and prints details about IP and ARP packets.
- **Packet Type Display:** Shows whether packets are outgoing, broadcast, multicast, or incoming.
- **Hexadecimal Dump:** Displays raw packet data in hexadecimal format for detailed analysis.

---

## ⚙️ Requirements

- **Linux Operating System:** Required for raw socket creation.
- **C Compiler:** Recommended compiler is **gcc**.
- **Root Privileges:** Superuser permissions are needed for creating raw sockets.

---

## 🔧 Building the Code
Use the provided **Makefile** to compile the program.

1. **Open a terminal.**
2. **Navigate** to the project directory containing the Makefile.
3. **Run** the following command to build the program:

```bash
make
```

---

## 💻 Usage
Run the compiled program with **root privileges**:

```bash
sudo ./packet_capture
```

The program will begin capturing packets and printing their details to the console. Use **Ctrl+C** to stop the program.

---

## 📚 Example Output

```plaintext
[+] Capturing packets...

Packet Type: Incoming
Source MAC: 00:1A:2B:3C:4D:5E
Destination MAC: FF:FF:FF:FF:FF:FF
Protocol: ARP
Payload (Hex): 00 01 08 00 06 04 00 01...

Packet Type: Outgoing
Source MAC: 00:1A:2B:3C:4D:5E
Destination MAC: 12:34:56:78:9A:BC
Protocol: IP
Payload (Hex): 45 00 00 34 12 34 40 00...
```

---

## ⚠️ Important Notes

- Use this program **only** for educational or authorized network analysis.
- Ensure network interface permissions are configured properly.
- The program supports basic packet types and can be extended for deeper analysis.

---

## ⭐ Support the Project
If you found this project helpful, consider giving it a **Star** ⭐ on GitHub! Contributions and suggestions are always welcome.

