#include "stdafx.h"
#include <stdarg.h>
#include "rc4.h"

void init(unsigned char *S)
{
    int i;

    for(i = 0; i < 256; i++)
        S[i] = i;
    return;
}

void swap(unsigned char *i, unsigned char *j)
{
    unsigned char temp;

    temp = *i;
    *i = *j;
    *j = temp;
}

void ksa(unsigned char *S, unsigned char *key)
{
    int i, j, keylen;

    j = 0;
    keylen = (int) strlen((char *) key);
    for(i = 0; i < 256; i++)
    {
        j = (j + S[i] + key[i % keylen]) % 256;
        swap(&S[i], &S[j]);
    }
    return;
}

unsigned char* prng(unsigned char *S, int len)
{
    int i, j, k;
    unsigned char *keystream;

    keystream = (unsigned char*)malloc(sizeof(unsigned char*) * len);
    if (keystream == NULL)
        return NULL;

    i = 0;
    j = 0;
    for(k = 0; k < len; k++)
    {
        i = (i + 1) % 256;
        j = (j+S[i]) % 256;
        swap(&S[i], &S[j]);
        keystream[k] = S[(S[i] + S[j]) % 256];
    }
    return keystream;
}

void rc4(unsigned char *key, unsigned char *input, unsigned char *output)
{
    int i;
    unsigned char S[256];
    unsigned char *keystream;

    memset(S, 0, 256);
    init(S);
    ksa(S, key);
    keystream = prng(S, strlen((char *) input));

    if (keystream == NULL)
        return;

    for(i = 0; i < (int) strlen((char *) input); i++)
        output[i] = input[i] ^ keystream[i];

    memset(S, 0, 256); 
    free(keystream);
}