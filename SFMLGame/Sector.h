#pragma once

#include <vector>

#include "Common.h"
#include "Linedef.h"

NAMESPACE_BEGIN

struct Sector
{
   std::vector<Linedef> linedefs;
};

NAMESPACE_END
