#ifndef OUTPUT_CSV__HPP
#define OUTPUT_CSV__HPP

/**
 * @file output_csv.hpp
 *
 * @brief Format the output of Mersenne Twister's Dynamic Creators.
 *	  Widely inspired from output.hpp shipping with MTGP's tool
 *	  package.
 *
 * @author Jonathan Passerat-Palmbach (ISIMA, Blaise Pascal University, France)
 * @author Mutsuo Saito (Hiroshima University)
 * @author Makoto Matsumoto (Hiroshima University)
 *
 * Copyright (c) 2010 Mutsuo Saito, Makoto Matsumoto and Hiroshima
 * University. All rights reserved.
 * Copyright (c) 2011 Mutsuo Saito, Makoto Matsumoto, Hiroshima
 * University and University of Tokyo. All rights reserved.
 * Copyright (c) 2012 Jonathan Passerat-Palmbach, ISIMA, Blaise Pascal
 * University, France. All rights reserved.
 *
 * The new BSD License is applied to this software, see LICENSE.txt
 */
#include <cstdint>
#include <iostream>
#include <fstream>
#include <all_in_one.hpp>
#include <random_util.hpp>

extern "C" {
#include <dc.h>
}

namespace parallelMT {
   namespace util {

      template<typename T>
	 static void output_params_stream(
	       mt_struct& param,
	       bool first,
	       std::ostream& ost) {

	    using namespace std;

	    int bit_size;
	    int width;
	    
	    if (sizeof(T) == 4) {
	       bit_size = 32;
	       width = 8;
	    } else {
	       bit_size = 64;
	       width = 16;
	    }

	    if (first) {
	       ost << "# type, ww, nn, mm, "
		  << "rr, aaa, shift0, maskD, shiftB, maskB, shiftC,"
		  << "maskC, shift1, init_mul" << endl;
	    }

	    // type
	    if (bit_size == 32) {
	       ost << "uint32_t,";
	    } else {
	       ost << "uint64_t,";
	    }

	    // ww, nn, mm, rr
	    ost << dec;
	    ost << param.ww << ",";
	    ost << param.nn << ",";
	    ost << param.ww << ",";
	    ost << param.rr << ",";

	    // aaa, shift0
	    ost << hex;
	    ost << "0x" << setw(width) << setfill('0') << param.aaa << ",";
	    ost << "0x" << setw(width) << setfill('0') << param.shift0 << ",";

	    // maskD
	    ost << "0x" << setw(width) << setfill('0');
	    if (bit_size == 32) {
	       ost << "ffffffff" << ","; 
	    }
	    else {
	       ost << "5555555555555555ull" << ","; 
	    }

	    // shiftB, maskB, shiftC, maskC, shift1
	    ost << "0x" << setw(width) << setfill('0') << param.shiftB << ",";
	    ost << "0x" << setw(width) << setfill('0') << param.maskB << ",";
	    ost << "0x" << setw(width) << setfill('0') << param.shiftC << ",";
	    ost << "0x" << setw(width) << setfill('0') << param.maskC << ",";
	    ost << "0x" << setw(width) << setfill('0') << param.shift1 << ",";

	    // init_mul
	    ost << dec;
	    if (bit_size == 32) {
	       ost << "1812433253" << ","; 
	    }
	    else {
	       ost << "6364136223846793005ull" << ","; 
	    }

	    ost << endl;
	 }

      template<typename T>
	 void output_mtgp_params(
	       mt_struct& param,
	       const std::string& filename,
	       bool first = true) {

	    using namespace std;

	    if (!opt.filename.empty()) {
	       // should check in parse param
	       ofstream ofs(filename.c_str(), std::ios::out | std::ios::app);
	       if (ofs) {
		  try {
		     output_params_stream<T>(param, first, ofs);
		     ofs.close();
		  } catch (...) {
		     ofs.close();
		  }
	       }
	    } else {
	       output_params_stream<T>(param, first, cout);
	    }
	 }

   } // end of namespace util
} // end of namespace parallelMT

#endif // OUTPUT_CSV_HPP

