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
   std::cerr << "Usage:\n\t" << binaryName << " <mersenne exponent> <output file name> <id>" << std::endl;
}

int main(int argc, char* argv[])
{
   if (argc != 4) {
      usage(argv[0]);
      exit(1);
   }
   
   int mersenneExponent;
   std::string filename(argv[2]);
   unsigned int id;

   if ( sscanf(argv[1], "%d", &mersenneExponent) != 1 ||
        filename.empty() ||
	sscanf(argv[3], "%u", &id) != 1) {
      usage(argv[0]);
      exit(2);
   }
 
   mt_struct *mts = NULL;

   mts = get_mt_parameter_id_st(sizeof(mt_output_t) * 8, mersenneExponent, id, 4172);
   if (mts == NULL) {
      std::cerr << "error\n" << std::endl;
   }
   else {
      parallelMT::util::output_mt_params<mt_output_t>(*mts, filename);
      free_mt_struct(mts);
   }

   return 0;
}

