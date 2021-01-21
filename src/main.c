#include <stdio.h>
#include "base64.h"

int main(void)
{
    char lol[] = "Hello";
    char encoded[1024] = {0};
    char decoded[1024] = {0};

    base64_encode(lol,encoded,sizeof(encoded));

    printf("%s\n",encoded);

    base64_decode(encoded,decoded,sizeof(decoded));

    printf("%s\n", decoded);

    free_decoding_table();

    return (0);
}