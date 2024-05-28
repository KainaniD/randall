#include "output.h"

bool writebytes(unsigned long long x, int nbytes) {
  do {
    if (putchar(x) < 0)
      return false;
    x >>= CHAR_BIT;
    nbytes--;
  } while (0 < nbytes);

  return true;
}

int handle_output(int nbytes) {
      /* Now that we know we have work to do, arrange to use the
     appropriate library.  */
  void (*initialize)(void);
  unsigned long long (*rand64)(void);
  void (*finalize)(void);
  if (rdrand_supported()) {
    initialize = hardware_rand64_init;
    rand64 = hardware_rand64;
    finalize = hardware_rand64_fini;
  } else {
    initialize = software_rand64_init;
    rand64 = software_rand64;
    finalize = software_rand64_fini;
  }

  initialize();
  int wordsize = sizeof rand64();
  int output_errno = 0;

  do {
    unsigned long long x = rand64();
    int outbytes = nbytes < wordsize ? nbytes : wordsize;
    if (!writebytes(x, outbytes)) {
      output_errno = errno;
      break;
    }
    nbytes -= outbytes;
  } while (0 < nbytes);

  if (fclose(stdout) != 0)
    output_errno = errno;

  if (output_errno) {
    errno = output_errno;
    perror("output");
  }

  finalize();
  return !!output_errno;
}