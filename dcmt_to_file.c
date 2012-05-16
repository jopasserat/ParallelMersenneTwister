/*
   This is a simple example for Dynamic Creator library.
 */

#include <cstdio>
#include <cstdlib>

extern "C" {
   #include <dc.h>
}

#include "output_csv.hpp"

int main(void)
{
   mt_struct *mts = NULL;

   /* This tries to find a small Mersenne Twister with period 2^521-1. */
   mts = get_mt_parameter_st(32,19937,4172);
   if (mts == NULL) {
      std::cerr << "error\n" << std::endl;
   }
   else {
      parallelMT::util::output_params(*mts, "mt_params.csv");
      free_mt_struct(mts);
   }

   return 0;
}

