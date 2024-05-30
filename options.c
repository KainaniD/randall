#include "options.h"

long long handle_nbytes(int argc, char **argv) {
    /* Check arguments.  */

    bool valid = false;
    long long nbytes;
    
    if (optind < argc) {
        char *endptr;
        errno = 0;
        nbytes = strtoll(argv[argc-1], &endptr, 10);
        if (errno)
            perror(argv[argc-1]);
        else
            valid = !*endptr && 0 <= nbytes;
    }
    
    if (!valid) {
        fprintf(stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
        return -1;
    }

    /* If there's no work to do, don't worry about which library to use.  */
    if (nbytes == 0)
        return -2;

    return nbytes;
}