/*
  encrypt.c
  20181203

  AESOnChip

  Benjamin Cholet
  Jean-Baptiste Valladeau

  Argument 1 : 128 bits key (32 char[] hex string)
  Argiment 2 : 128 text to encrypt (32 char[] hex string)

  Output : cypher text

  No Initialisation vector used
*/

#include <stdio.h>
#include <stdlib.h> // for strtol
#include <string.h> //for strlen
#include "aes.h"

int main(int argc, char *argv[]) {

    // Check the args validity
    if(argc != 3) {   

        printf("Invalid number of arguments.\nUsage:\n./encrypt.run key text\n");
        return 1;
    }

    if(strlen(argv[1]) != 32 || strlen(argv[2]) != 32) {

        printf("Invalid key/text size.\n");
        return 1;
    }

    uint8_t key[16];
    uint8_t text[16];
    struct AES_ctx ctx;

    // Get the key & text from the args
    for(int i = 0; i < 16; i++) {

        char key_str[3] = { argv[1][2*i], argv[1][2*i+1], '\0' };
        char text_str[3] = { argv[2][2*i], argv[2][2*i+1], '\0' };

        key[i] = (uint8_t) strtol(key_str, NULL, 16);
        text[i] = (uint8_t) strtol(text_str, NULL, 16);
    }   

    /* Initialize context calling one of: */
    AES_init_ctx(&ctx, key);

    AES_ECB_encrypt(&ctx, text);

    printf("Output is :\n");
    for (int i = 0; i < 16; ++i) {

        printf("%.2X", text[i]);
    }
    printf("\n");

    return 0;
}
