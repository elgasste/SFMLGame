#pragma once

#include <vector>

#include "Common.h"
#include "Sector.h"
#include "BspNode.h"

NAMESPACE_BEGIN

class Game;
class GameData;
class GameConfig;

class GameLoader
{
public:
   std::shared_ptr<Game> Load() const;
   std::shared_ptr<GameData> LoadGameData( std::shared_ptr<GameConfig> gameConfig ) const;
private:
   
   std::vector<Sector> LoadSectors() const;
   BspNode* LoadBspTree( std::vector<Sector>& sectors ) const;
};

NAMESPACE_END
