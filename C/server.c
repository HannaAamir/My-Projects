// Hanna Aamir
// Lab 2, Spring 2024
// CSCI 3761 001
// Prof. Ogle
// Due Date: April 17, 2024
// server.c (server file)

#include <arpa/inet.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
// defines the buffer size for data handling
#define BUF_SIZE 1024

// structure to represent a dhcp packet
struct dhcp_packet {
  uint8_t op;          // Operation codee
  uint32_t ciaddr;     // ip address for client
  uint32_t yiaddr;     // the client's ip address
  uint32_t fromIPAddr; // ip address of where packet is from, should be 0.0.0.0
                       // on client->server
  uint32_t toIPAddr; // ip address of destination, should be 255.255.255.255 on
                     // client->server
  uint16_t transID;  // transaction ID
};

int main(int argc, char *argv[]) {
  // verify that the correct number of arguments were passed
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <port> <server_ip>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int port = atoi(argv[1]); // port conversion, string to integer
  char *server_ip =
      argv[2]; // Server's ip address from the command line argument

  int sockfd; // descriptor for socket
  struct sockaddr_in server_addr,
      client_addr;         // Socket address structures for server and client
  socklen_t client_length; // length of the client address structure
  struct dhcp_packet datagram; // instance of dhcp packet

  // Creating a UDP socket
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    perror("socket.");
    exit(EXIT_FAILURE);
  }

  // Enabling the broadcast option on the socket
  int broadcasting = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcasting,
                 sizeof(broadcasting)) == -1) {
    perror("setsockopt failed.");
    exit(EXIT_FAILURE);
  }

  // setting up server address structure and binding the socket
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port);
  if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  printf("Server listening on port %d...\n", port);

  // infinite loop to receive and process datagrams continuously
  while (1) {
    client_length = sizeof(client_addr);
    // Receive request from client
    ssize_t received_bytes =
        recvfrom(sockfd, &datagram, sizeof(datagram), 0,
                 (struct sockaddr *)&client_addr, &client_length);
    if (received_bytes < 0) {
      perror("recvfrom");
      exit(EXIT_FAILURE);
    }

    // Validate DHCP request in the if statement
    if (datagram.op == 1 && datagram.fromIPAddr == 0 &&
        datagram.toIPAddr == htonl(0xFFFFFFFF)) {
      // print the packet information
      printf("DHCP datagram is:\n");
      printf("op: %u\n", datagram.op);
      printf("ciaddr: %u\n", datagram.ciaddr);
      printf("offered IP Address: %s\n",
             inet_ntoa(*(struct in_addr *)&datagram.yiaddr));
      printf("fromIPAddr: %s\n",
             inet_ntoa(*(struct in_addr *)&datagram.fromIPAddr));
      printf("toIPAddr: %s\n",
             inet_ntoa(*(struct in_addr *)&datagram.toIPAddr));
      printf("TranID: %u\n", datagram.transID);

      // prepare the dhcp reply packet for client
      struct dhcp_packet offer_packet;
      memset(&offer_packet, 0, sizeof(offer_packet));
      offer_packet.op = 2;
      offer_packet.ciaddr = 1;
      offer_packet.yiaddr = htonl(0xC0A80164);
      offer_packet.fromIPAddr =
          inet_addr(server_ip); // Converting server_ip to network byte order
      offer_packet.toIPAddr = htonl(0xFFFFFFFF);
      offer_packet.transID =
          datagram.transID; // Set the transaction ID same as received datagram

      // send the dhcp offer back to the client
      if (sendto(sockfd, &offer_packet, sizeof(offer_packet), 0,
                 (struct sockaddr *)&client_addr, client_length) < 0) {
        perror("sendto");
        exit(EXIT_FAILURE);
      }
    }
  }

  close(sockfd);

  return 0;
}