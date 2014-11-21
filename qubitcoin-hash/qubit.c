
#include "qubit.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "sph_luffa.h"
#include "sph_cubehash.h"
#include "sph_shavite.h"
#include "sph_simd.h"
#include "sph_echo.h"


static __inline uint32_t
be32dec(const void *pp)
{
	const uint8_t *p = (uint8_t const *)pp;

	return ((uint32_t)(p[3]) + ((uint32_t)(p[2]) << 8) +
	    ((uint32_t)(p[1]) << 16) + ((uint32_t)(p[0]) << 24));
}

static __inline void
be32enc(void *pp, uint32_t x)
{
	uint8_t * p = (uint8_t *)pp;

	p[3] = x & 0xff;
	p[2] = (x >> 8) & 0xff;
	p[1] = (x >> 16) & 0xff;
	p[0] = (x >> 24) & 0xff;
}

static __inline uint32_t
le32dec(const void *pp)
{
	const uint8_t *p = (uint8_t const *)pp;

	return ((uint32_t)(p[0]) + ((uint32_t)(p[1]) << 8) +
	    ((uint32_t)(p[2]) << 16) + ((uint32_t)(p[3]) << 24));
}

static __inline void
le32enc(void *pp, uint32_t x)
{
	uint8_t * p = (uint8_t *)pp;

	p[0] = x & 0xff;
	p[1] = (x >> 8) & 0xff;
	p[2] = (x >> 16) & 0xff;
	p[3] = (x >> 24) & 0xff;
}

/*
 * Encode a length len/4 vector of (uint32_t) into a length len vector of
 * (unsigned char) in big-endian form.  Assumes len is a multiple of 4.
 */
static void
be32enc_vect(unsigned char *dst, const uint32_t *src, size_t len)
{
	size_t i;

	for (i = 0; i < len / 4; i++)
		be32enc(dst + i * 4, src[i]);
}

/*
 * Decode a big-endian length len vector of (unsigned char) into a length
 * len/4 vector of (uint32_t).  Assumes len is a multiple of 4.
 */
static void
be32dec_vect(uint32_t *dst, const unsigned char *src, size_t len)
{
	size_t i;

	for (i = 0; i < len / 4; i++)
		dst[i] = be32dec(src + i * 4);
}





/* Move init out of loop, so init once externally, and then use one single memcpy with that bigger memory block */
/*
typedef struct {
	sph_luffa512_context 	luffa1;
	sph_cubehash512_context cubehash1;
	sph_shavite512_context  shavite1;
	sph_simd512_context		simd1;
	sph_echo512_context		echo1;
} qubithash_context_holder;

qubithash_context_holder base_contexts;

void init_qubithash_contexts()
{
   // sph_blake512_init(&base_contexts.blake1);
  sph_luffa512_init(&base_contexts.luffa1);
  sph_cubehash512_init(&base_contexts.cubehash1);
  sph_shavite512_init(&base_contexts.shavite1);
  sph_simd512_init(&base_contexts.simd1);
  sph_echo512_init(&base_contexts.echo1);
}
*/
void qubit_hash(const char* input, char* output)
{
	sph_luffa512_context 	ctx_luffa;
	sph_cubehash512_context ctx_cubehash;
	sph_shavite512_context  ctx_shavite;
	sph_simd512_context		ctx_simd;
	sph_echo512_context		ctx_echo;
//        static unsigned char pblank[1];


//	qubithash_context_holder ctx;

	//these uint512 in the c++ source of the client are backed by an array of uint32
    uint32_t hashA[16], hashB[16];	
	
	//do one memcopy to get fresh contexts, its faster even with a larger block then issuing 9 memcopies
//	memcpy(&ctx, &base_contexts, sizeof(base_contexts));
	
    
    sph_luffa512_init (&ctx_luffa);
    sph_luffa512 (&ctx_luffa, input, 80);
    sph_luffa512_close (&ctx_luffa, hashA);	
	

    sph_cubehash512_init (&ctx_cubehash);   
    sph_cubehash512 (&ctx_cubehash, hashA, 64);   
    sph_cubehash512_close(&ctx_cubehash, hashB);  
	

    sph_shavite512_init (&ctx_shavite);   
    sph_shavite512 (&ctx_shavite, hashB, 64);   
    sph_shavite512_close(&ctx_shavite, hashA);  
	
	sph_simd512_init (&ctx_simd);   
	sph_simd512 (&ctx_simd, hashA, 64);   
    sph_simd512_close(&ctx_simd, hashB); 
	
	sph_echo512_init (&ctx_echo);   
	sph_echo512 (&ctx_echo, hashB, 64);   
    sph_echo512_close(&ctx_echo, hashA);

	memcpy(output, hashA, 32);

}
