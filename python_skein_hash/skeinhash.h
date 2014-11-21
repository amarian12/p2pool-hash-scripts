#ifndef SKEINHASH_H
#define SKEINHASH_H

#include "sph_skein.h"
#include "sph_sha2.h"

void sha256_hash(const char* input, size_t input_len, char* output);
void skein_hash(const char *input, size_t input_len, char* output);

#endif
