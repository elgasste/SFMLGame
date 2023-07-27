#pragma once

#include <vector> // MUFFINS

#include "Common.h"
#include "Sector.h" // MUFFINS
#include "BspNode.h" // MUFFINS

NAMESPACE_BEGIN

class Game;
class GameData;

class GameLoader
{
public:
   std::shared_ptr<Game> Load() const;
   std::shared_ptr<GameData> LoadGameData() const;
private:
   
   std::vector<Sector> LoadSectors() const;
   BspNode* LoadBspTree( std::vector<Sector>& sectors ) const;
};

NAMESPACE_END
