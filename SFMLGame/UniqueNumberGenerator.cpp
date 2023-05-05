#include "UniqueNumberGenerator.h"

using namespace NAMESPACE;

UniqueNumberGenerator::UniqueNumberGenerator() :
   _currentNumber( 0 )
{
}

unsigned int UniqueNumberGenerator::Generate()
{
   _currentNumber++;
   return _currentNumber;
}