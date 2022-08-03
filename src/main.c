#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client.h"
#include "server.h"

const char help[] =
    "Exchange quantum-resistant safe data.\n\n\
Parameters: [server|client]\n\
- server: start listening socket\n\
- client: start and connect to server\n";

int main(int argc, char const *argv[]) {
  if (argc == 1) {
    printf(help);
  } else {
    const char *mode = argv[1];
    if (strcmp(mode, "client") == 0)
      socket_client();
    else if (strcmp(mode, "server") == 0)
      socket_server();
    else {
      // printf("Invalid parameters\n\n");
      printf(help);
    }
  }
  return 0;
}

