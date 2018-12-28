#include <stdio.h>
#include <string.h>
#include "md5.h"

int main()
{
    int i;
    /*bb2cfdeaa87e23cdb893f46abb230006*/
    unsigned char* a = (unsigned char*)"addecafafasdfasdfasdd";
    unsigned char b[16] = {0};
    MD5_CTX md5;
    Md5Init(&md5);
    Md5Update(&md5, a, strlen((char *)a));
    Md5Final(&md5, b);
    printf("%s\n", a);
    for (i = 0; i < 16; i++) {
        printf("%02x", b[i]);
    }
    
    printf("\n");

    return 0;
}
