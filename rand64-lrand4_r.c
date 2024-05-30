#include "rand64-lrand4_r.h"

struct drand48_data state;

void hardware_mrand4_init(void) {}

/* Return a random value, using hardware operations.  */
unsigned long long hardware_mrand4(void) {
	long int data1;
    long int data2;
	// Initialize PRNG using time
	srand48_r(time(NULL), &state);
	// Get random value
	lrand48_r(&state, &data1);

	// Initialize PRNG using time
	srand48_r(time(NULL), &state);
	// Get random value
	lrand48_r(&state, &data2);

	return (data1 << 32) + data2;
}

void hardware_mrand4_fini(void) {}
