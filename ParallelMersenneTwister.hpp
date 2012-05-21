/*
 *  ParallelMersenneTwister.hpp
 *  
 *
 *  Created by Jonathan PASSERAT-PALMBACH on 5/15/12 following
 *  Luc TOURAILLE's advice.
 *  Copyright 2012 ISIMA/LIMOS. All rights reserved.
 *
 */

#ifndef PARALLEL_MERSENNE_TWISTER
#define PARALLEL_MERSENNE_TWISTER

#include <map>
#include <boost/thread/thread.hpp>

/** ParallelMersenneTwister is a wrapper class that enables polymorphism
   within the hierarachy of independant MersenneTwister parameters set.
 */
template <typename T>
class ParallelMersenneTwister {

public:
   typedef std::map<boost::thread::id, unsigned int> idStore_t;
   typedef T result_type;
   
private:   
   static idStore_t                       actualIds_;
   static unsigned int                    idCount_;
   static boost::mutex                    mutex_;   

public:
   // make it compliant with boost to enable distributions
   virtual result_type next() = 0;
   virtual result_type operator()() = 0;
   virtual result_type min() = 0;
   virtual result_type max() = 0;
   
   ParallelMersenneTwister();
   
   /** static method to get the MT assigned to a particular thread */
   static ParallelMersenneTwister<T>* getParallelMersenneTwister();
   
};


/** Concrete implementation of the PRNG.
   Instances will differ from each other by the MT parameter: i.e. the independent
   Mersenne Twister model.
 */
template <typename T, class MT>
class ParallelMersenneTwister_impl : public ParallelMersenneTwister<T> {
   MT gen_;
   
public:

   // boost like methods
   T next() {
      return gen_();
   }
   
   T operator()() {
      return gen_();
   }
   
   T min() {
      return gen_.min();
   }   
   
   T max() {
      return gen_.max();
   }
};

// methods definition

#include "mersenneTwister_instances.hpp"

template <typename T>
ParallelMersenneTwister<T>::ParallelMersenneTwister () {
   
   boost::thread::id                       threadId = boost::this_thread::get_id();
   
   // entering critical section
   boost::lock_guard <boost::mutex> (mutex_);
   
   // figure out actual "understandable" Id
   if ( actualIds_.find(threadId) == 
       actualIds_.end() ) {
      actualIds_[threadId] = idCount_++;
   }

} // out of critical section 


/** This function enables threads to pick up the independent instance of MT
    corresponding to their unique identifier.
    The identifier is determined by a call to boost::this_thread::get_id()
   that returns an hexadecimal unique id for each thread.
   @return A pointer to the independent MT instance assigned to the calling thread.
 */
template <typename T>
ParallelMersenneTwister<T>* ParallelMersenneTwister<T>::getParallelMersenneTwister() {
   
   boost::thread::id                       threadId = boost::this_thread::get_id();
   
   boost::lock_guard <boost::mutex> (mutex_);
   
   
   return MTParametersArray<T>::generators[ actualIds_[threadId ] ];
}


// static members definition
template <typename T>
std::map<boost::thread::id, unsigned int>      ParallelMersenneTwister<T>::actualIds_;

template <typename T>
unsigned int                                   ParallelMersenneTwister<T>::idCount_;

template <typename T>
boost::mutex                                   ParallelMersenneTwister<T>::mutex_;


#endif // PARALLEL_MERSENNE_TWISTER

