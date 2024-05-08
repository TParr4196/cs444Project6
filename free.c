#include "image.h"
#include "block.h"
#include "free.h"

#define BITS_PER_BYTE 8

void set_free(unsigned char *block, int num, int set){
    int byte=block[num/BITS_PER_BYTE];
    int bit_index=num % BITS_PER_BYTE;
    block[num/BITS_PER_BYTE]=(byte &(1 << bit_index)) | (set << bit_index);
    //source is bitmanip.c from discord: my solution was much clunkier 
}

int find_free(unsigned char *block){
    unsigned char byte;

    for (int i = 0; i < BLOCK_SIZE; i++) {
        byte = block[i];
        if (byte == 0xff)
            continue;

        for (int j = 0; j < BITS_PER_BYTE; j++) {
            if (!(byte & (1 << j)))
                return i * BITS_PER_BYTE + j;
        }
    }

    return -1;
    //source for continue block and byte declaration is ffz.c from discord
}