#ifndef __C_GENERIC_HASH_H__
#define __C_GENERIC_HASH_H__

#include <stdint.h>

/**
 * The djb2 hash, created by Daniel J. Bernstein, is a fast, simple, non-cryptographic string hash algorithm known for excellent distribution. It initializes with 5381, iteratively multiplies by 33, and adds each byte, typically producing a 32-bit hash, often using (hash << 5) + hash for speed.  
*/
uint32_t hash_djb2(const char* string);

#endif