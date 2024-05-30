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

int handle_output(char *input, char *output, int nbytes) {
  /* Now that we know we have work to do, arrange to use the
     appropriate library.  */
  void (*initialize_hardware)(void);
  void (*initialize_software)(char*);
  unsigned long long (*rand64)(void);
  void (*finalize)(void);

  //Error handling for missing input or output
  if (input[0] == '\0' || output[0] == '\0'){
    fprintf(stderr, "Missing input or output\n");
    return 1;
  }

  if (strcmp(input, "rdrand") == 0) {
    // Handles hardware case
    initialize_hardware = hardware_rand64_init;
    rand64 = hardware_rand64;
    finalize = hardware_rand64_fini;
    initialize_hardware();
  } else if (strcmp(input, "lrand48_r") == 0) {
    // Handles lrand48_r case
    initialize_hardware = hardware_mrand4_init;
    rand64 = hardware_mrand4;
    finalize = hardware_mrand4_fini;
    initialize_hardware();
  } else {
    // Handle /F case.
    if (strncmp(input, "/", 1) != 0) {
      fprintf(stderr, "Invalid input file\n");
      return 1;
    }
    initialize_software = software_rand64_init;
    rand64 = software_rand64;
    finalize = software_rand64_fini;
    initialize_software(input);
  }

  int wordsize = sizeof rand64();
  int output_errno = 0;

   if (strcmp(output, "stdio") == 0) {
      // Default stdio option
      do {
      unsigned long long x = rand64();
      int outbytes = nbytes < wordsize ? nbytes : wordsize;
      if (!writebytes(x, outbytes)) {
        output_errno = errno;
        break;
      }
      nbytes -= outbytes;
      } while (0 < nbytes);

   } else {

      do {
        int N = atoi(output);
        if (N <= 0){
          fprintf(stderr, "ERROR, N is not valid\n");
          return 1;
        }

        char* buf = malloc(sizeof(char) * N);
        if (buf == NULL){
          fprintf(stderr, "ERROR, memory not allocated\n");
          return 1;
        }
        unsigned long long x = rand64();
        unsigned long long *ptr = &x;
        memcpy(buf, ptr, N);
        int written = write(1, buf, N);

        free(buf); 
        nbytes -= written;
      } while (0 < nbytes);
   }

  if (fclose(stdout) != 0)
    output_errno = errno;

  if (output_errno) {
    errno = output_errno;
    perror("output");
  }

  finalize();
  return !!output_errno;
}