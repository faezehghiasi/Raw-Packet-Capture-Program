# Packet Sniffer (Raw Packet Capture)

A lightweight **C-based** packet sniffer that captures Ethernet, IP, TCP, and UDP packets and saves them to a **.pcap** file for analysis in **Wireshark**.

## 🚀 Features
✔ Captures raw network packets  
✔ Extracts **MAC, IP, TCP, and UDP** headers  
✔ Saves packets to a `.pcap` file  
✔ Lightweight and fast  

## 🛠 Installation
Install **libpcap** before compiling:

**Ubuntu/Debian:**
```sh
sudo apt install libpcap-dev -y
```
**Fedora:**
```sh
sudo dnf install libpcap-devel -y
```
**Arch Linux:**
```sh
sudo pacman -S libpcap
```

## 🔨 Usage

1️⃣ **Compile the program**  
```sh
make
```

2️⃣ **Run the sniffer**  
```sh
sudo make run
```

3️⃣ **View packets in Wireshark**  
```sh
wireshark captured.pcap
```

## ⚙ Makefile Commands
| Command       | Description                     |
|--------------|---------------------------------|
| `make`       | Compile the program            |
| `make run`   | Run the program (requires sudo) |
| `make clean` | Remove compiled files & logs   |

## 📌 Example Output
```sh
[+] Capturing packets...

Packet Type: Incoming
Source MAC: AA:BB:CC:DD:EE:FF
Destination MAC: 11:22:33:44:55:66
Protocol: IP
Source IP: 192.168.1.10
Destination IP: 8.8.8.8
Protocol: UDP
Source Port: 53
Destination Port: 443
```

  


