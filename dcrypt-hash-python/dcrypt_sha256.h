// Copyright (c) 2013-2014 The Slimcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SHA256_H
#define SHA256_H

#include <stdint.h>
#include <stdbool.h>

#include <openssl/sha.h>
 
#define SHA256_LEN           64 //64 bytes the for the hash itself

//the intermediate sha256 hashing algoritm
void sha256_to_str(const unsigned char *data, size_t data_sz, unsigned char *outputBuffer, unsigned char *hash_digest);
uint32_t *sha256(const unsigned char *data, size_t data_sz, uint32_t *hash_digest);

void sha256_salt_to_str(const unsigned char *data, size_t data_sz, unsigned char *salt, size_t salt_sz, 
                        unsigned char *outputBuffer, unsigned char *hash_digest);

void digest_to_string(unsigned char *hash_digest, unsigned char *string);

#endif
