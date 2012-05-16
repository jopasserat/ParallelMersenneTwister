/*
   This is a simple example for Dynamic Creator library.
 */

#include <cstdio>
#include <cstdlib>

extern "C" {
   #include <dc.h>
}

#include "output_csv.hpp"

typedef uint32_t mt_output_t;

int main(void)
{
   mt_struct *mts = NULL;

   /* This tries to find a small Mersenne Twister with period 2^521-1. */
   mts = get_mt_parameter_st(sizeof(mt_output_t),19937,4172);
   if (mts == NULL) {
      std::cerr << "error\n" << std::endl;
   }
   else {
      parallelMT::util::output_mt_params<mt_output_t>(*mts, "mt_params.csv");
      free_mt_struct(mts);
   }

   return 0;
}

