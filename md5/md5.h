#ifndef _MD5_H
#define _MD5_H

#ifdef _cplusplus
extern "C" {
#endif

typedef struct
{
    unsigned int count[2];
    unsigned int state[4];
    unsigned char buffer[64];
}MD5_CTX;

#define F(x, y, z) ((x & y) | (~x & z))
#define G(x, y, z) ((x & z) | (y & ~z))
#define H(x, y, z) (x ^ y ^ z)
#define I(x, y, z) (y ^ (x | ~z))
#define ROTATE_LEFT(x, n) ((x << n) | (x >> (32 - n)))

#define FF(a, b, c, d, x, s, ac)\
        {\
         a += F(b, c, d) + x + ac;\
         a = ROTATE_LEFT(a, s);\
         a += b;\
        }

#define GG(a, b, c, d, x, s, ac)\
        {\
         a += G(b, c, d) + x + ac;\
         a = ROTATE_LEFT(a, s);\
         a += b;\
        }

#define HH(a, b, c, d, x, s, ac)\
        {\
         a += H(b, c, d) + x + ac;\
         a = ROTATE_LEFT(a, s);\
         a += b;\
        }

#define II(a, b, c, d, x, s, ac)\
        {\
         a += I(b, c, d) + x + ac;\
         a = ROTATE_LEFT(a, s);\
         a += b;\
        }

void Md5Init(MD5_CTX *inContext);
void Md5Update(MD5_CTX *inContext, unsigned char *inStr, unsigned int inStrLen);
void Md5Final(MD5_CTX *inContext, unsigned char digest[16]);

#ifdef _cplusplus
}
#endif

#endif
