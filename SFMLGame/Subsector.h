#pragma once

#include <vector>

#include "Common.h"
#include "Sector.h"
#include "Lineseg.h"

NAMESPACE_BEGIN

struct Subsector
{
   std::vector<Lineseg> linesegs;
};

NAMESPACE_END
