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
   std::shared_ptr<std::vector<Sector>> LoadSectors() const;
   BspNode* LoadBspTree( std::shared_ptr<std::vector<Sector>> sectors ) const;
   void ScaleMap( std::shared_ptr<GameData> gameData, float scalar ) const;
   void ScaleTreeRecursive( BspNode* node, float scalar ) const;

   std::shared_ptr<RenderData> LoadRenderData() const;
};

NAMESPACE_END
