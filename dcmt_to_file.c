/**
   @file dcmt_to_file.c
   Calls Dynamic Creator and stores its results into a CSV file.

   @author Jonathan PASSERAT-PALMBACH
*/

#include <cstdio>
#include <cstdlib>

extern "C" {
   #include <dc.h>
}

#include "output_csv.hpp"

typedef uint32_t mt_output_t;

void usage(const std::string& binaryName) {
   std::cerr << "Usage:\n\t" << binaryName << " <mersenne exponent> <output file name>" << std::endl;
}

int main(int argc, char* argv[])
{
   if (argc != 3) {
      usage(argv[0]);
      exit(1);
   }
   
   int mersenneExponent;
   std::string filename(argv[2]);

   if ( sscanf(argv[1], "%d", &mersenneExponent) != 1 ||
        filename.empty() ) {
      usage(argv[0]);
      exit(2);
   }
 
   mt_struct *mts = NULL;

   mts = get_mt_parameter_st(sizeof(mt_output_t) * 8, mersenneExponent, 4172);
   if (mts == NULL) {
      std::cerr << "error\n" << std::endl;
   }
   else {
      parallelMT::util::output_mt_params<mt_output_t>(*mts, filename);
      free_mt_struct(mts);
   }

   return 0;
}

