#include "skeinhash.h"

void sha256_hash(const char* input, size_t input_len, char* output)
{
    sph_sha256_context context;
    
    sph_sha256_init(&context);
    sph_sha256(&context, (const void*)input, sizeof(char) * input_len);
    sph_sha256_close(&context, (void*)output);
}

void skein_hash(const char *input, size_t input_len, char* output) 
{
    sph_skein512_context context;
    char skein512_hash[64];
    
    sph_skein512_init(&context);
    sph_skein512(&context, (const void*)input, sizeof(char) * input_len);
    sph_skein512_close(&context, (void*)&skein512_hash);
    
    sha256_hash((const char*)&skein512_hash, 64, output);
}
