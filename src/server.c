#include "server.h"

#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "crypto.h"
#include "util.h"

#define SA struct sockaddr

static uint8_t pk[KEM_PKL];
static uint8_t sk[KEM_SKL];

static int acceptClient() {
  // TODO, for now, aceptation because the client has the pk, and the pk is
  // never distributed next steps can be:
  //  - either accept authentication from the non-PQ servers (the IAM)
  //  - or use a Diffie-Hellman like by using keys ofor client and server
  //  - or also use a trusted signed key (or cert with a PQ-fork of SSL)
  return 0;
}

static void* handler_server(void* args) {
  int status = 0;
  if (acceptClient() != 0) {
    fprintf(stderr, "Client is not authorized");
    return (void*)401;
  }
  size_t MAX = KEM_CTL;
  int connfd = *(int*)args;
  uint8_t buff[MAX];
  memset(buff, 0, MAX);
  char* OK = "ok";
  char* ERROR = "error";

  // Read cipthertext
  size_t len = read(connfd, buff, sizeof(buff));
  if (len <= 0) {
    fprintf(stderr, "Client was closed\n");
    close(connfd);
    return (void*)410;
  }
  if (len != MAX) {
    fprintf(stderr, "Client sent invalid payload\n");
    close(connfd);
    return (void*)410;
  }
  uint8_t* ct = buff;
  uint8_t ss[KEM_SSL];
  status = KEM_DECAPSULATE(sk, ct, ss);
  log8("", ss, KEM_SSL);

  // Send result to client
  char* response = NULL;
  if (status == 0) {
    response = OK;
  } else {
    fprintf(stderr, "Error when decapsulating the shared key");
    response = ERROR;
  }
  len = write(connfd, response, strlen(response) + 1);
  if (len <= 0) fprintf(stderr, "Client is not available\n");
  close(connfd);

  return (void*)0;
}

static int generate_keys(uint8_t* pk, size_t pkl, uint8_t* sk, size_t skl) {
  int status = 0;
  printf("Generating new pair of keys\n");
  // Raise error if keys exist
  FILE* pkf = fopen("public.pem", "r");
  FILE* skf = fopen("private.pem", "r");
  if (pkf != NULL || skf != NULL) {
    fprintf(stderr,
            "key files already exist."
            "You must remove or backup them before generating new key files\n");
    return 409;
  }
  status = KEM_GENKEYS(pk, sk);
  if (status != 0) {
    fprintf(stderr, "Error when generating the keys\n");
    return 500;
  }
  size_t len = 0;

  const char p1[] = "-----BEGIN PUBLIC KEY-----\n";
  const char p2[] = "\n-----END PUBLIC KEY-----\n";
  const char s1[] = "-----BEGIN PRIVATE KEY-----\n";
  const char s2[] = "\n-----END PRIVATE KEY-----\n";

  char* str = base64_encode(pk, pkl, &len);
  pkf = fopen("public.pem", "w");
  fwrite(p1, 1, strlen(p1), pkf);
  fwrite(str, 1, len, pkf);
  fwrite(p2, 1, strlen(p2), pkf);
  fclose(pkf);

  str = base64_encode(sk, skl, &len);
  skf = fopen("private.pem", "w");
  fwrite(s1, 1, strlen(s1), skf);
  fwrite(str, 1, len, skf);
  fwrite(s2, 1, strlen(s2), skf);
  fclose(skf);

  return status;
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
    fprintf(stderr,
            "The real key length does not match the expected key length");
    return 500;
  }
  memcpy(key, buf, bufl);
  return 0;
}

static int load_keys(uint8_t* pk, size_t pkl, uint8_t* sk, size_t skl) {
  int status = 0;

  // Check keys and generate first time
  FILE* pkf = fopen("public.pem", "r");
  FILE* skf = fopen("private.pem", "r");
  if (pkf == NULL && skf == NULL) {
    status = generate_keys(pk, pkl, sk, skl);
    if (status != 0) return status;
  }
  if (pkf != NULL) fclose(pkf);
  if (skf != NULL) fclose(skf);

  // Load keys
  status += load_key("public.pem", pk, pkl);
  status += load_key("private.pem", sk, skl);
  return status;
}

int socket_server(int PORT) {
  // Load KEM keys
  int status = 0;
  status = load_keys(pk, KEM_PKL, sk, KEM_SKL);
  if (status != 0) return status;

  // Create socket server
  int sockfd, connfd;
  unsigned int len;
  struct sockaddr_in servaddr, cli;
  int on = 1;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    fprintf(stderr, "Socket creation failed\n");
    exit(0);
  }
  memset(&servaddr, 0, sizeof(servaddr));

  // Params
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);

  // Prevent bind error on restarts
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

  // Bind socket
  if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
    fprintf(stderr, "Socket bind failed (another server in same port?).\n");
    exit(0);
  }
  // Listen for incoming clients
  if ((listen(sockfd, 5)) != 0) {
    fprintf(stderr, "Listen failed\n");
    exit(0);
  }  // else    printf("Server listening at port %d ...\n", PORT);
  len = sizeof(cli);

  // Run continuosly
  while (1 == 1) {
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
      fprintf(stderr, "Server accept failed\n");
      exit(0);
    }  // else  printf("server accepts the socket client...\n");
    pthread_t thread;
    int id = connfd;
    pthread_create(&thread, NULL, handler_server, (void*)&id);
  }

  close(sockfd);
  return 0;
}