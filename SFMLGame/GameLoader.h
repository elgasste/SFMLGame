#pragma once

#include <vector>

#include "Common.h"
#include "Sector.h"
#include "BspNode.h"

NAMESPACE_BEGIN

class Game;
class GameData;
class GameConfig;
class Entity;
class RenderData;

class GameLoader
{
public:
   std::shared_ptr<Game> Load() const;

private:
   std::shared_ptr<GameData> LoadGameData( std::shared_ptr<GameConfig> gameConfig ) const;
   std::vector<Sector> LoadSectors() const;
   BspNode* LoadBspTree( std::vector<Sector>& sectors ) const;
   void ScaleUnits( std::vector<Sector>& sectors, BspNode* bspTree, std::shared_ptr<Entity> player, float scalar ) const;
   void ScaleTreeRecursive( BspNode* node, float scalar ) const;

   std::shared_ptr<RenderData> LoadRenderData() const;
};

NAMESPACE_END
