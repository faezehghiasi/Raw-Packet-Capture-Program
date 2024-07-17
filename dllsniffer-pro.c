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

int main() {

     int sockfd;
    sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully.\n");
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

        if (protocol == ETH_P_IP) {
            printf("Upper Protocol :IP ");
            int eth_header_len = 14;
            struct iphdr *ip = (struct iphdr *)(buffer + eth_header_len);
            unsigned int ip_header_len = ip->ihl * 4;
            unsigned short total_length = ntohs(ip->tot_len);
            unsigned char upper_protocol = ip->protocol;
            printf("(header len: %u , ", ip_header_len);
            printf("total len: %u , ", total_length);
            printf("proto : %u ), ", upper_protocol);
            
        } else if (protocol == ETH_P_ARP) {
            printf("Upper Protocol :ARP , ");
        } else {
            printf("Incoming packet with unknown protocol: 0x%04x , ", protocol);
        }
        switch (phyaddr.sll_pkttype) {
            case PACKET_OUTGOING:
                printf("Outgoing:\n");
                break;
            case PACKET_BROADCAST:
                printf("Broadcast:\n");
                break;
            case PACKET_MULTICAST:
                printf("Multicast:\n");
                break;
            case PACKET_HOST:
                printf("Incoming:\n");
                break;
            default:
                printf("Other:\n");
                break;
        }
        for (int i = 0; i < numbytes; i++) {
            printf("%02x ", (unsigned char)buffer[i]);
        }

        printf("\n\n");

    }
    close(sockfd);
    return 0;
}
