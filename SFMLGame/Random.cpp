#include <random>

#include "Random.h"

using namespace NAMESPACE;
using namespace std;

namespace
{
   random_device r_device;
   mt19937 rng( r_device() );
   uniform_int_distribution<mt19937::result_type> r_distribution;
}

unsigned int Random::GetUnsignedInt( unsigned int min, unsigned int max ) const
{
   return ( r_distribution( r_device ) % ( ( max + 1 ) - min ) ) + min;
}
