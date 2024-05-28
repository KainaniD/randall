#ifndef OUTPUT_HEADER
#define OUTPUT_HEADER

#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include "rand64-hw.h"
#include "rand64-sw.h"

bool writebytes(unsigned long long x, int nbytes);

int handle_output(int nbytes);

#endif