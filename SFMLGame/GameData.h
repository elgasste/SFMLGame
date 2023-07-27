#pragma once

#include <vector>

#include "Common.h"
#include "Sector.h"

NAMESPACE_BEGIN

class GameData
{
public:
   GameData( std::vector<Sector> sectors );

   std::vector<Sector>& GetSectors() { return _sectors; }

private:
   std::vector<Sector> _sectors;
};

NAMESPACE_END
