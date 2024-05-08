#include "image.h"
#include "block.h"
#include "ctest.h"

#ifdef CTEST_ENABLE

void test_image_open(void){
    CTEST_ASSERT(image_fd==-1, "testing initialization of image_fd");
    CTEST_ASSERT(image_open("image.txt",0)>=0, "testing image_open");
}

void test_image_close(void){
    CTEST_ASSERT(image_close()==0, "testing image_close");
}

void test_bread_bwrite(void){
    unsigned char block_map[4096]={1,1,1,1,1,1};
    CTEST_ASSERT(bread(2,block_map)==block_map, "testing bread");
    unsigned char buffer[4096]={0};
    bwrite(2,buffer);
    CTEST_ASSERT(*buffer==*block_map, "testing bwrite");
}

int main(){
    CTEST_VERBOSE(1);

    test_image_open();

    test_bread_bwrite();

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

    unsigned char block_map[4096]={1,1,1,1,1,1};
    bread(2,block_map);

    unsigned char inode_data_block_0[4096]={0};
    bread(3,inode_data_block_0);

    unsigned char inode_data_block_1[4096]={0};
    bread(4,inode_data_block_1);

    unsigned char inode_data_block_2[4096]={0};
    bread(5,inode_data_block_2);

    unsigned char inode_data_block_3[4096]={0};
    bread(3,inode_data_block_3);

    //unsure what the data blocks should contain other than block map so left empty for now
    
    image_close();
}

#endif