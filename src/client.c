#include "client.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "crypto.h"
#include "util.h"

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

static int load_key(const char* path, uint8_t* key, size_t keyl);

static int handler_client(int sockfd) {
  // ---Create the shared secret---
  int status = 0;
  uint8_t pk[KEM_PKL];
  status = load_key("public.pem", pk, KEM_PKL);
  if (status != 0) {
    perror("Unable to load the public key.\n");
    return 400;
  }
  uint8_t ct[KEM_CTL];
  uint8_t ss[KEM_SSL];
  status = KEM_ENCAPSULATE(pk, ss, ct);
  log8("Client key is:", ss, KEM_SSL);

  // ---Send the ciphertext to server---
  size_t len = write(sockfd, ct, KEM_CTL);
  if (len <= 0) {
    perror("Server is not available.\n");
    return 500;
  }
  // ---Server to accept or reject the shared secret---
  uint8_t response[100];
  len = read(sockfd, response, 100);
  if (len <= 0) {
    perror("Server was closed\n");
    return 500;
  }
  printf("Server response: %s\n", response);
  return 0;
}

/**
 * Load a .pem file containing a key into an array
 */
static int load_key(const char* path, uint8_t* key, size_t keyl) {
  FILE* file;
  file = fopen(path, "r");
  if (file == NULL) {
    fprintf(stderr, "File containing the key was not found\n");
    return 404;
  }
  char c;

  // Skip first line
  while ((c = fgetc(file)) != '\n') {
    ;
  }

  int KEY_LEN = 0;
  char str[10000];
  while ((c = fgetc(file)) != '\n') {
    str[KEY_LEN] = c;
    KEY_LEN++;
  }
  fclose(file);

  str[KEY_LEN] = '\0';
  size_t bufl = 0;
  uint8_t* buf = base64_decode(str, strlen(str), &bufl);
  if (bufl > keyl) {
    printf("Error: The real key length does not match the expected key length");
    return 500;
  }
  memcpy(key, buf, bufl);
  return 0;
}

int socket_client() {
  int sockfd;
  struct sockaddr_in servaddr;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("socket creation failed...\n");
    exit(0);
  } else
    printf("Socket successfully created..\n");
  memset(&servaddr, 0, sizeof(servaddr));

  // Connect
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr.sin_port = htons(PORT);
  if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
    printf("connection with the server failed...\n");
    exit(0);
  } else
    printf("connected to the server..\n");

  int status = handler_client(sockfd);

  close(sockfd);
  return status;
}
