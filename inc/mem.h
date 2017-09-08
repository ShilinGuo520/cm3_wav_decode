#include "types.h"

#define MEM_BASE    0x2000a000
#define MEM_SIZE    0x00005000  //20K
#define BLOCK_SIZE  0x4         //byt

#define MAP_SIZE    (MEM_SIZE/BLOCK_SIZE/8)

extern void * malloc(int size);
extern int free(void *mem);
extern void memcpy(unsigned char *dec, unsigned char *src, int size);
extern void memset(unsigned char *src, unsigned char val, int size);

