#include <stdint.h>

// #define Debug 0 // debug mode

#define u16 uint16_t
#define WIDTH sizeof(uint16_t)

#define REG_NUM 16 // register amount

/* the starting address of the program */
#define START 0x3000

#define getop(x) x >> 12

#define MEMORY_MAX ( 1 << 16 )