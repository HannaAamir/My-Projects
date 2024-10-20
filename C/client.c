// Hanna Aamir
// Lab 2, Spring 2024
// CSCI 3761 001
// Prof. Ogle
// Due Date: April 17, 2024
// client.c (client file)

#include <arpa/inet.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define BUF_SIZE 1024

// structure for dhcp packet
struct dhcp_packet {
  uint8_t op;          // Operation code
  uint32_t ciaddr;     // client's ip address
  uint32_t yiaddr;     // ip address for client
  uint32_t fromIPAddr; // ip address of server sending the packet
  uint32_t
      toIPAddr; // Broadcast address which should be 255.255.255.255 in requests
  uint16_t transID; // transaction ID
};

int main(int argc, char *argv[]) {
  // this verifies the correct number of command line arguments
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <server_port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // this converts the command line argument to an integer for port
  int server_port = atoi(argv[1]);

  int sockfd;                     // the socket descriptor
  struct sockaddr_in server_addr; // address strucure for the server
  char buffer[BUF_SIZE];          // buffer for data

  srand(time(NULL)); // seed the random number generator
  // Creating a udp socket
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    perror("socket.");
    exit(EXIT_FAILURE);
  }

  // Set socket option to enable broadcasting
  int broadcasting = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcasting,
                 sizeof(broadcasting)) == -1) {
    perror("setsockopt failed.");
    exit(EXIT_FAILURE);
  }

  // initialize the dhcp request packet
  struct dhcp_packet request_packet;
  memset(&request_packet, 0, sizeof(request_packet));
  request_packet.op = 1;
  request_packet.fromIPAddr =
      inet_addr("0.0.0.0"); // from ip address 0.0.0.0 (unspecific)
  request_packet.toIPAddr = htonl(0xFFFFFFFF); // the broadcast
  request_packet.ciaddr = 0;
  request_packet.yiaddr = 0;
  request_packet.transID = rand(); // generate a random transaction ID

  // Broadcasting the request to the server
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
  server_addr.sin_port = htons(server_port);
  if (sendto(sockfd, &request_packet, sizeof(request_packet), 0,
             (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("sendto");
    exit(EXIT_FAILURE);
  }

  printf("DHCP request broadcasted.\n");

  // Wait for response from the server after sending dhcp request packet
  ssize_t bytes_received = recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);
  if (bytes_received < 0) {
    perror("recvfrom");
    exit(EXIT_FAILURE);
  }

  // interepret the response as a dhcp packet
  struct dhcp_packet *server_response = (struct dhcp_packet *)buffer;
  // validate the server's response
  if (server_response->op != 2 ||
      server_response->toIPAddr != inet_addr("255.255.255.255")) {
    fprintf(stderr, "Invalid DHCP response.\n");
    exit(EXIT_FAILURE);
  }

  // Display details of the received DHCP packet
  printf("DHCP Packet is:\n");
  printf("Op: %d\n", server_response->op);
  printf("Ciaddr: %u\n", server_response->ciaddr);
  printf("offered IP Address: %s\n",
         inet_ntoa(*(struct in_addr *)&server_response->yiaddr));
  printf("fromIPAddr: %s\n",
         inet_ntoa(*(struct in_addr *)&server_response->fromIPAddr));
  printf("toIPAddr: %s\n",
         inet_ntoa(*(struct in_addr *)&server_response->toIPAddr));
  printf("TranID: %u\n", server_response->transID);

  close(sockfd);

  return 0;
}
