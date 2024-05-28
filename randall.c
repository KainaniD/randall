/* Generate N bytes of random output.  */

/* When generating output this program uses the x86-64 RDRAND
   instruction if available to generate random numbers, falling back
   on /dev/random and stdio otherwise.

   This program is not portable.  Compile it with gcc -mrdrnd for a
   x86-64 machine.

   Copyright 2015, 2017, 2020 Paul Eggert

   This program is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include "options.h"
#include "output.h"

/* Main program, which outputs N bytes of random data.  */
int main(int argc, char **argv) {
  int nbytes = handle_nbytes(argc, argv);

  if (nbytes == 1){
        fprintf(stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
    return 1;
  } else if (nbytes == 0) {
    return 0;
  }

  return handle_output(nbytes);
}
