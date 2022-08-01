#include "client.h"
#include "electrocomms.h"
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
      printf("Invalid parameters");
      exit(1);
    }
  }
  return 0;
}

void log8(char *text, uint8_t *data, size_t len) {
  // size_t LIMIT = len;
  size_t LIMIT = len < 32 ? len : 32;
  printf("%s", text);
  for (size_t r = 0; r < LIMIT; r++) printf("%02x", *data++);
  if (len > LIMIT) printf("...%zu bytes", len);
  printf("\n");
}