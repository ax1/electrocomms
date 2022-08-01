#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

static void handler(int sockfd) {
  char buff[MAX];
  int n;
  for (;;) {
    memset(buff, 0, sizeof(buff));
    printf("Enter the string : ");
    n = 0;
    while ((buff[n++] = getchar()) != '\n')
      ;
    size_t len = write(sockfd, buff, sizeof(buff));
    if (len <= 0) {
      printf("Server is not available\n");
      break;
    }
    memset(buff, 0, sizeof(buff));
    len = read(sockfd, buff, sizeof(buff));
    if (len <= 0) {
      printf("Server was closed\n");
      break;
    }
    printf("From Server : %s", buff);
  }
}

int main() {
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

  handler(sockfd);

  close(sockfd);
}
