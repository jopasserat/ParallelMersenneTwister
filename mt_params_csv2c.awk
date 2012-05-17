#!/usr/bin/awk -f
#####
# Simple awk file to fill-in C++ table source of MT parameters
# Inspired from Saito & Matsumoto's  fast-param.awk
#
# Copyright Jonathan PASSERAT-PALMBACH, 2012
#####

BEGIN {
    FS=","
    first = 1;
   # count = 0;
}
END {
    printf("\n");
    printf("\n// end of dynamic part \n");
    printf("};\n");
}

/^#/ {next}
{
    if (first) {
	first = 0;
	first_out();
    }
    middle_out();
}

function first_out() {
   printf("/*");
   printf(" *  @file mersenneTwister_instances.hpp\n");
   printf(" *  \n");
   printf(" *  Automatically generated file, DO NOT EDIT!\n");
   printf(" *\n");
   printf(" *  Created by Jonathan PASSERAT-PALMBACH on 5/16/12.\n");
   printf(" *  Copyright 2012 ISIMA/LIMOS. All rights reserved.\n");
   printf(" *\n");
   printf(" */\n");
   printf(" \n");
   printf(" // beginning of constant part\n");
   printf(" #include <boost/random/mersenne_twister.hpp>\n");
   printf(" \n");
   printf(" template <typename T>\n");
   printf(" struct MTParametersArray {\n");
   printf("    static ParallelMersenneTwister<T>* generators[];\n");
   printf(" };\n");
   printf("\n");
   printf("\n");
   printf("template <typename T>\n");
   printf("ParallelMersenneTwister<T>* MTParametersArray<T>::generators[]  = {\n");
   printf("// beginning of dynamic part   \n");

   connect = "\n";
}

function middle_out() {
    # break previous line
    printf("%s", connect);
 
    type = $1
    ww = $2
    nn = $3
    mm = $4
    rr = $5
    aaa = $6
    shift0 = $7
    maskD = $8
    shiftB = $9
    maskB = $10
    shiftC = $11
    maskC = $12
    shift1 = $13
    init_mul = $14

    printf("\tnew ParallelMersenneTwister_impl<T, boost::random::mersenne_twister_engine < %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s >()",
	       type, ww, nn, mm, rr, aaa, shift0, maskD, shiftB, maskB, shiftC, maskC, shift1, init_mul);
   # prepare next line
    connect = ",\n";
#    count++;
}

