#include "server.h"

#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

static void* handler_server(void* args) {
  int connfd = *(int*)args;
  char buff[MAX];
  char* response = "ACK\n";
  for (;;) {
    // Read
    memset(buff, 0, MAX);
    size_t len = read(connfd, buff, sizeof(buff));
    printf("%s (read bytes %li)\n", buff, len);

    // If client disconnects, read() is invoked with 0 len (or -1)
    if (len <= 0) {
      printf("Client was closed\n");
      close(connfd);
      break;
    }

    // Write
    len = write(connfd, response, strlen(response) + 1);
    if (len <= 0) {
      printf("Client is not available\n");
      break;
    }
    printf("(write bytes %li)\n", len);
  }
  return NULL;
}

void load_keys(uint8_t* pk, uint8_t* sk) {}

void socket_server() {
  int sockfd, connfd;
  unsigned int len;
  struct sockaddr_in servaddr, cli;
  int on = 1;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("Socket creation failed...\n");
    exit(0);
  } else
    printf("Socket successfully created..\n");
  memset(&servaddr, 0, sizeof(servaddr));

  // Params
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);

  // Prevent bind error on restarts
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

  // Bind socket
  if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
    printf("socket bind failed...\n");
    exit(0);
  } else
    printf("Socket successfully binded..\n");

  // Listen for incoming clients
  if ((listen(sockfd, 5)) != 0) {
    printf("Listen failed...\n");
    exit(0);
  } else
    printf("Server listening..\n");
  len = sizeof(cli);

  // Run continuosly
  while (1 == 1) {
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
      printf("server accept failed...\n");
      exit(0);
    } else
      printf("server accept the client...\n");
    pthread_t thread;
    int id = connfd;
    pthread_create(&thread, NULL, handler_server, (void*)&id);
  }

  close(sockfd);
}