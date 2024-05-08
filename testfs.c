#include "image.h"
#include "block.h"
#include "free.h"
#include "inode.c"
#include "ctest.h"

#ifdef CTEST_ENABLE

void test_image_open(void){
    CTEST_ASSERT(image_open("image.txt",0)>=0, "image_open returns file descriptor");
}

void test_image_close(void){
    CTEST_ASSERT(image_close()==0, "image_close close() success");
}

void test_bread_bwrite(void){
    unsigned char block_map[4096]={1,1,1,1,1,1};
    CTEST_ASSERT(bread(2,block_map)==block_map, "bread returns buffer");
    unsigned char buffer[4096]={0};
    bwrite(2,buffer);
    CTEST_ASSERT(*buffer==*block_map, "bwrite fills buffer with disk image and bread was successful");
}

//void test_alloc(void){}

void test_set_free(void){
    unsigned char block[16]={0};
    set_free(block, 3, 1);
    set_free(block, 17, 1);
    set_free(block, 13, 0);
    set_free(block, 42, 1);
    unsigned char byte=block[0];
    int chk1 = byte & (1 << 3);
    byte=block[2];
    int chk2 = byte & (1 << 1);
    byte=block[1];
    int chk3 = !(byte & (1 << 5));
    byte=block[5];
    int chk4 = byte & (1 << 2);
    CTEST_ASSERT(chk1&&chk2&&chk3&&chk4, "set_free arbitrary sets verified");
}

void test_find_free(void){
    unsigned char block[4096]={0};
    for(int i=0; i<BLOCK_SIZE; i++){
        block[i]=0xff;
    }
    CTEST_ASSERT(find_free(block)==-1, "find free returns -1 if block is full");
    set_free(block, 2, 0);
    set_free(block, 5, 0);
    set_free(block, 12, 0);
    set_free(block, 22, 0);
    int chk1 = find_free(block)==2;
    set_free(block, 2, 1);
    int chk2 = find_free(block)==5;
    set_free(block, 5, 1);
    int chk3 = find_free(block)==12;
    set_free(block, 12, 1);
    int chk4 = find_free(block)==22;
    CTEST_ASSERT(chk1&&chk2&&chk3&&chk4, "find_free arbitrary empty values verified");
}

//void test_ialloc(void){}

int main(){
    CTEST_VERBOSE(1);

    test_image_open();

    test_bread_bwrite();

    test_set_free();

    test_find_free();

    //test_alloc();

    //test_ialloc();

    test_image_close();

    CTEST_RESULTS();

    CTEST_EXIT();
}

#else

int main(){

    image_open("image.txt",0);

    unsigned char superblock[4096]={0};
    bread(0,superblock);

    unsigned char inode_map[4096]={0};
    bread(1,inode_map);

    unsigned char block_map[4096]={0};
    bread(2,block_map);

    unsigned char inode_data_block_0[4096]={0};
    bread(3,inode_data_block_0);

    unsigned char inode_data_block_1[4096]={0};
    bread(4,inode_data_block_1);

    unsigned char inode_data_block_2[4096]={0};
    bread(5,inode_data_block_2);

    unsigned char inode_data_block_3[4096]={0};
    bread(6,inode_data_block_3);
    //initialize the data blocks as empty
    
    image_close();
}

#endif