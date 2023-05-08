#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class Random
{
public:
   int GetInt( int min, int max ) const;
   float GetFloat( float min, float max ) const;
};

NAMESPACE_END
