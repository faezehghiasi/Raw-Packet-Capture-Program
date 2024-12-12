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

void print_mac_address(unsigned char *mac) {
    printf("%02X:%02X:%02X:%02X:%02X:%02X", 
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

int main() {
    int sockfd;
    sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("[+] Capturing packets...\n\n");

    char buffer[2048];
    struct sockaddr_ll phyaddr;
    socklen_t addr_len = sizeof(struct sockaddr_ll);

    while (1) {
        int numbytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&phyaddr, &addr_len);
        if (numbytes < 0) {
            perror("Recvfrom failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        struct ethhdr *eth = (struct ethhdr *)buffer;
        unsigned short protocol = ntohs(eth->h_proto);

        printf("Packet Type: ");
        switch (phyaddr.sll_pkttype) {
            case PACKET_OUTGOING: printf("Outgoing\n"); break;
            case PACKET_BROADCAST: printf("Broadcast\n"); break;
            case PACKET_MULTICAST: printf("Multicast\n"); break;
            case PACKET_HOST: printf("Incoming\n"); break;
            default: printf("Other\n"); break;
        }

        printf("Source MAC: ");
        print_mac_address(eth->h_source);
        printf("\nDestination MAC: ");
        print_mac_address(eth->h_dest);

        if (protocol == ETH_P_IP) {
            printf("\nProtocol: IP\n");
        } else if (protocol == ETH_P_ARP) {
            printf("\nProtocol: ARP\n");
        } else {
            printf("\nProtocol: Unknown (0x%04X)\n", protocol);
        }

        printf("Payload (Hex): ");
        for (int i = 0; i < numbytes; i++) {
            printf("%02X ", (unsigned char)buffer[i]);
        }
        printf("\n\n");
    }
    close(sockfd);
    return 0;
}
