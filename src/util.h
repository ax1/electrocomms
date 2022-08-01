#ifndef ELECTROCOMMS_UTIL_H
#define ELECTROCOMMS_UTIL_H
#include <stddef.h>
#include <stdint.h>
char *base64_encode(uint8_t *data, size_t input_length, size_t *output_length);
uint8_t *base64_decode(const char *data, size_t input_length,
                       size_t *output_length);
#endif