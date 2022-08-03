#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client.h"
#include "server.h"

const char help[] =
    "Exchange quantum-resistant safe data.\n\n\
Parameters: [server | client]\n\
- server: start listening socket. Format: server [PORT (default 8080)]\n\
- client: start and connect to server. Format client [[HOST (default 127.0.0.1) [PORT (default 8080)]]\n";

int main(int argc, char const *argv[]) {
  if (argc == 1) {
    printf(help);
  } else {
    const char *mode = argv[1];
    char *HOST = "127.0.0.1";
    int PORT = 8080;
    if (strcmp(mode, "client") == 0) {
      if (argc > 2) HOST = (char *)argv[2];
      if (argc > 3) PORT = atoi(argv[3]);
      socket_client(HOST, PORT);
    } else if (strcmp(mode, "server") == 0) {
      if (argc > 2) PORT = atoi(argv[2]);
      socket_server(PORT);
    } else {
      // printf("Invalid parameters\n\n");
      printf(help);
    }
  }
  return 0;
}

