#include <stdio.h>
#include <stdlib.h>

#include "electrocomms.h"
#include "kyber1024/api.h"

// int main(int argc, char const *argv[]) {
int main() {
  uint8_t pk[KEM_PKL];
  uint8_t sk[KEM_SKL];
  int status = KEM_GENKEYS(pk, sk);
  log8("pk: ", pk, KEM_PKL);
  printf("status=%d\n", status);
  return status;
}

void log8(char *text, uint8_t *data, size_t len) {
  // size_t LIMIT = len;
  size_t LIMIT = len < 32 ? len : 32;
  printf("%s", text);
  for (size_t r = 0; r < LIMIT; r++) printf("%02x", *data++);
  if (len > LIMIT) printf("...%zu bytes", len);
  printf("\n");
}