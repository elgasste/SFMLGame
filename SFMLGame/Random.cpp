#include <random>

#include "Random.h"

using namespace NAMESPACE;
using namespace std;

namespace
{
   random_device r_device;
   mt19937 rng( r_device() );
}

int Random::GetInt( int min, int max ) const
{
   uniform_int_distribution<int> distribution( min, max );
   return distribution( r_device );
}

float Random::GetFloat( float min, float max ) const
{
   uniform_real_distribution<float> distribution( min, max );
   return distribution( r_device );
}
