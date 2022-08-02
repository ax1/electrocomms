#ifndef ELECTROCOMMS_UTIL_H
#define ELECTROCOMMS_UTIL_H
#include <stddef.h>
#include <stdint.h>

// Base64
char *base64_encode(const uint8_t *data, size_t input_length,
                    size_t *output_length);
uint8_t *base64_decode(const char *data, size_t input_length,
                       size_t *output_length);
// Hex<>Arr conversion
size_t hex_to_uint8(const char *src, uint8_t *dest);

// Log
void log8(char *text, uint8_t *data, size_t len);

#endif