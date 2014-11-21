// Copyright (c) 2013-2014 The OpenSSL developers
// Copyright (c) 2013-2014 The Slimcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>        //for strlen

#include "dcrypt_sha256.h"

//static void digest_to_string(unsigned char *hash_digest, unsigned char *string)
void digest_to_string(unsigned char *hash_digest, unsigned char *string)
{
  register unsigned char tmp_val;

  uint32_t i = 0;
  for(; i < SHA256_DIGEST_LENGTH; i++)
  {
    //format the most (left-most) significant 4bit hex
    tmp_val = *(hash_digest + i) >> 4;

    //get the integer into a char
    if(tmp_val <= 9)
      *(string + (i * 2)) = tmp_val + '0';
    else //add 87 to get the integer into the a-f of a hex
      *(string + (i * 2)) = tmp_val + 87; //ex: if tmp_val == 10 (0xa) then + 87 equals char 'a'

    //format the least (right-most) significant 4bit hex
    tmp_val = *(hash_digest + i) & 0x0F;

    //get the integer into a char
    if(tmp_val <= 9)
      *(string + (i * 2) + 1) = tmp_val + '0';
    else //add 87 to get the integer into the a-f of a hex
      *(string + (i * 2) + 1) = tmp_val + 87; //ex: if tmp_val == 10 (0xa) then + 87 equals char 'a'

  }

  //add the termination \000 to the string
  *(string + SHA256_LEN) = 0;
  
  return;
}

void sha256_to_str(const unsigned char *data, size_t data_sz, unsigned char *outputBuffer, unsigned char *hash_digest)
{
  SHA256_CTX sha256;
  static unsigned char __digest__[SHA256_DIGEST_LENGTH];

  if(hash_digest == NULL)
    hash_digest = __digest__;

  SHA256_Init(&sha256);
  SHA256_Update(&sha256, data, data_sz);
  SHA256_Final(hash_digest, &sha256);

  //convert the digest to a string
  digest_to_string(hash_digest, outputBuffer);

  //sucess!
  return;
}

//optional arg: hash_digest
// same code from openssl lib, just a bit more specialized
uint32_t *sha256(const unsigned char *data, size_t data_sz, uint32_t *hash_digest)
{
  SHA256_CTX hash;

  SHA256_Init(&hash);
  SHA256_Update(&hash, data, data_sz);
  SHA256_Final((unsigned char*)hash_digest, &hash);
  //~ OPENSSL_cleanse(&hash, sizeof(hash));

  return hash_digest;
}

void sha256_salt_to_str(const unsigned char *data, size_t data_sz, unsigned char *salt, size_t salt_sz, 
                        unsigned char *outputBuffer, unsigned char *hash_digest)
{
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, data, data_sz);
  SHA256_Update(&sha256, salt, salt_sz);
  SHA256_Final(hash_digest, &sha256);

  //convert the digest to a string
  digest_to_string(hash_digest, outputBuffer);    

  //sucess!
  return;
}
