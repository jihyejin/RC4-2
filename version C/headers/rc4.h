#ifndef _RC4_H_
#define _RC4_H_

#include <stdlib.h>
#include <string.h>
#include <memory.h>

void init(unsigned char *S);

void swap(unsigned char *i, unsigned char *j);

void ksa(unsigned char *S, unsigned char *key);

unsigned char* prng(unsigned char *S, int len);

void rc4(unsigned char *key, unsigned char *input, unsigned char *output);

#endif /* _RC4_H_ */