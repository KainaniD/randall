#include "rand64-hw.h"

/* Hardware implementation.  */

struct cpuid cpuid(unsigned int leaf, unsigned int subleaf) {
  struct cpuid result;
  asm("cpuid"
      : "=a"(result.eax), "=b"(result.ebx), "=c"(result.ecx), "=d"(result.edx)
      : "a"(leaf), "c"(subleaf));
  return result;
}

_Bool rdrand_supported(void) {
  struct cpuid extended = cpuid(1, 0);
  return (extended.ecx & bit_RDRND) != 0;
}

void hardware_rand64_init(void) {}

/* Return a random value, using hardware operations.  */
unsigned long long hardware_rand64(void) {
  unsigned long long int x;

  /* Work around GCC bug 107565
     <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=107565>.  */
  x = 0;

  while (!_rdrand64_step(&x))
    continue;
  return x;
}

void hardware_rand64_fini(void) {}