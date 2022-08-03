#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client.h"
#include "server.h"

const char help[] =
    "Exchange quantum-resistant safe data.\n\n\
Parameters: [host] [|] [port]\n\
- server: start as listener. Example: ./electrocomms 8080\n\
- client: start and connect to server. Example: ./electrocomms 127.0.0.1 8080\n";

int main(int argc, char const *argv[]) {
  if (argc == 1) {
    printf(help);
  } else {
    if (argc == 2) {
      const int port = atoi(argv[1]);
      socket_server(port);
    } else if (argc == 3) {
      const char *host = argv[1];
      const int port = atoi(argv[2]);
      socket_client(host, port);
    } else {
      printf(help);
    }
  }
  return 0;
}

