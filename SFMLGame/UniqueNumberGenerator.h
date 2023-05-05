#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class UniqueNumberGenerator
{
public:
   UniqueNumberGenerator();

   unsigned int Generate();

private:
   unsigned int _currentNumber;
};

NAMESPACE_END
