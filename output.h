#ifndef OUTPUT_HEADER
#define OUTPUT_HEADER

#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include "rand64-hw.h"
#include "rand64-sw.h"
#include "rand64-lrand4_r.h"

bool writebytes(unsigned long long x, int nbytes);

int handle_output(char *input, char *output, int nbytes);

#endif