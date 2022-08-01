
#include "electrocomms.h"
#include "kyber1024/api.h"

void log8(char *text, uint8_t *data, size_t len) {
  // size_t LIMIT = len;
  size_t LIMIT = len < 32 ? len : 32;
  printf("%s", text);
  for (size_t r = 0; r < LIMIT; r++) printf("%02x", *data++);
  if (len > LIMIT) printf("...%zu bytes", len);
  printf("\n");
}

static int testKEM() {
  uint8_t pk[KEM_PKL];
  uint8_t sk[KEM_SKL];
  uint8_t ct[KEM_CTL];
  uint8_t ss[KEM_SSL];
  int status = KEM_GENKEYS(pk, sk);
  log8("pk: ", pk, KEM_PKL);
  status += KEM_ENCAPSULATE(pk, ss, ct);
  log8("ss: ", ss, KEM_SSL);
  memset(ss, 0, KEM_SSL);
  status += KEM_DECAPSULATE(sk, ct, ss);
  log8("ss: ", ss, KEM_SSL);
  printf("status=%d\n", status);
  if (status != 0) exit(500);
  return status;
}

int main() { return testKEM(); }
