/**
 * Header for abstracting the algorithm names
 *
 * When selecting another algorithm, change the names only in this header,
 * so the C code calls an variables will not be refactored.
 *
 */
#ifndef ELECTROCOMMS_CRYPTO_H
#define ELECTROCOMMS_CRYPTO_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kyber1024/api.h"

#define KEM_SKL PQCLEAN_KYBER1024_CLEAN_CRYPTO_SECRETKEYBYTES
#define KEM_PKL PQCLEAN_KYBER1024_CLEAN_CRYPTO_PUBLICKEYBYTES
#define KEM_CTL PQCLEAN_KYBER1024_CLEAN_CRYPTO_CIPHERTEXTBYTES
#define KEM_SSL PQCLEAN_KYBER1024_CLEAN_CRYPTO_BYTES

#define KEM_NAME PQCLEAN_KYBER1024_CLEAN_CRYPTO_ALGNAME

static inline int KEM_GENKEYS(uint8_t *pk, uint8_t *sk) {
  return PQCLEAN_KYBER1024_CLEAN_crypto_kem_keypair(pk, sk);
}

static inline int KEM_ENCAPSULATE(const uint8_t *pk, uint8_t *ss, uint8_t *ct) {
  return PQCLEAN_KYBER1024_CLEAN_crypto_kem_enc(ct, ss, pk);
}

static inline int KEM_DECAPSULATE(const uint8_t *sk, const uint8_t *ct,
                                  uint8_t *ss) {
  return PQCLEAN_KYBER1024_CLEAN_crypto_kem_dec(ss, ct, sk);
}
#endif
