#include "block.h"
#include "image.h"
#include <stdio.h>
#include <unistd.h>

const int BLOCK_SIZE = 4096;
//block size of the disk we are representing

unsigned char *bread(int block_num, unsigned char *block){

    int chk=lseek(image_fd, block_num*BLOCK_SIZE, SEEK_SET);
    if(chk<0) fprintf(stderr, "lseek failed");
    //move global file descriptor to location corresponding to block_num and check if it worked

    chk=write(image_fd, block, BLOCK_SIZE);
    if(chk<0) fprintf(stderr, "write failed");
    //write from the buffer and check if it worked

    return block;
    //return buffer
}

void bwrite(int block_num, unsigned char *block){

    int chk=lseek(image_fd, block_num*BLOCK_SIZE, SEEK_SET);
    if(chk<0) fprintf(stderr, "lseek failed");
    //move global file descriptor to location corresponding to block_num and check if it worked

    chk=read(image_fd, block, BLOCK_SIZE);
    if(chk<0) fprintf(stderr, "write failed");
    //read from the buffer to the "disk" and check if it worked
}