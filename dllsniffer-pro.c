#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <errno.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <pcap.h>

void print_mac(unsigned char *mac) {
    printf("%02X:%02X:%02X:%02X:%02X:%02X", 
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void save_packet(pcap_dumper_t *dumper, const char *data, int len, struct timeval ts) {
    struct pcap_pkthdr header;
    header.ts = ts;
    header.caplen = len;
    header.len = len;
    pcap_dump((u_char *)dumper, &header, (const u_char *)data);
}

int main() {
    int sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("[+] Capturing packets...\n\n");

    char buffer[2048];
    struct sockaddr_ll addr;
    socklen_t addr_len = sizeof(addr);

    pcap_t *pcap = pcap_open_dead(DLT_EN10MB, 65535);
    pcap_dumper_t *dumper = pcap_dump_open(pcap, "capture.pcap");
    if (!dumper) {
        perror("Failed to open pcap dump file");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        int bytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&addr, &addr_len);
        if (bytes < 0) {
            perror("Recvfrom failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        struct ethhdr *eth = (struct ethhdr *)buffer;
        unsigned short proto = ntohs(eth->h_proto);

        printf("Packet Type: ");
        switch (addr.sll_pkttype) {
            case PACKET_OUTGOING: printf("Outgoing\n"); break;
            case PACKET_BROADCAST: printf("Broadcast\n"); break;
            case PACKET_MULTICAST: printf("Multicast\n"); break;
            case PACKET_HOST: printf("Incoming\n"); break;
            default: printf("Other\n"); break;
        }

        printf("Source MAC: ");
        print_mac(eth->h_source);
        printf("\nDestination MAC: ");
        print_mac(eth->h_dest);

        if (proto == ETH_P_IP) {
            printf("\nProtocol: IP\n");

            struct iphdr *ip = (struct iphdr *)(buffer + sizeof(struct ethhdr));
            struct in_addr src_ip, dest_ip;
            src_ip.s_addr = ip->saddr;
            dest_ip.s_addr = ip->daddr;

            printf("Source IP: %s\n", inet_ntoa(src_ip));
            printf("Destination IP: %s\n", inet_ntoa(dest_ip));

            if (ip->protocol == IPPROTO_TCP) {
                struct tcphdr *tcp = (struct tcphdr *)(buffer + sizeof(struct ethhdr) + sizeof(struct iphdr));
                printf("Protocol: TCP\n");
                printf("Source Port: %d\n", ntohs(tcp->source));
                printf("Destination Port: %d\n", ntohs(tcp->dest));
            } else if (ip->protocol == IPPROTO_UDP) {
                struct udphdr *udp = (struct udphdr *)(buffer + sizeof(struct ethhdr) + sizeof(struct iphdr));
                printf("Protocol: UDP\n");
                printf("Source Port: %d\n", ntohs(udp->source));
                printf("Destination Port: %d\n", ntohs(udp->dest));
            } else if (ip->protocol == IPPROTO_ICMP) {
                printf("Protocol: ICMP\n");
            } else {
                printf("Protocol: Unknown (0x%02X)\n", ip->protocol);
            }
        } else if (proto == ETH_P_ARP) {
            printf("\nProtocol: ARP\n");
        } else {
            printf("\nProtocol: Unknown (0x%04X)\n", proto);
        }

        struct timeval ts;
        gettimeofday(&ts, NULL);
        save_packet(dumper, buffer, bytes, ts);

        printf("\nPayload (Hex): ");
        for (int i = 0; i < bytes; i++) {
            printf("%02X ", (unsigned char)buffer[i]);
        }
        printf("\n\n");
    }

    pcap_dump_close(dumper);
    pcap_close(pcap);
    close(sockfd);
    return 0;
}