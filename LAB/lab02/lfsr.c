#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */
    int x = 0;
    x ^= (*reg) & 1;
    x ^= ((*reg) >> 2) & 1;
    x ^= ((*reg) >> 3) & 1;
    x ^= ((*reg) >> 5) & 1;
    *reg >>= 1;
    int mask = 1 << 15;
    *reg = ((x << 15) | ((*reg) & ~mask));
}

