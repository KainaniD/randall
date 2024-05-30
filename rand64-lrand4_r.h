#ifndef HARDWARE_MRAND4_HEADER
#define HARDWARE_MRAND4_HEADER

#include <stdio.h>
#include <stdlib.h> // for lrand48_r
#include <time.h> // for time

void hardware_mrand4_init(void);

unsigned long long hardware_mrand4(void);

void hardware_mrand4_fini(void);

#endif