#pragma once

#include <vector> // MUFFINS

#include "Common.h"
#include "Sector.h" // MUFFINS
#include "BspNode.h" // MUFFINS

NAMESPACE_BEGIN

class Game;

class GameLoader
{
public:
   std::shared_ptr<Game> Load() const;

private:
   // MUFFINS
   std::vector<Sector> LoadSectors() const;
   BspNode* LoadBspTree( std::vector<Sector>& sectors ) const;
};

NAMESPACE_END
