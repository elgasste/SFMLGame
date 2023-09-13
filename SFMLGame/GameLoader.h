#pragma once

#include "Common.h"
#include "BspNode.h"

NAMESPACE_BEGIN

class Game;
class GameData;
class GameConfig;
class RenderData;
class RenderConfig;
class GameClock;

class GameLoader
{
public:
   std::shared_ptr<Game> Load() const;

private:
   std::shared_ptr<GameData> LoadGameData( std::shared_ptr<GameConfig> gameConfig ) const;
   std::shared_ptr<RenderData> LoadRenderData( std::shared_ptr<RenderConfig> renderConfig,
                                               std::shared_ptr<GameData> gameData,
                                               std::shared_ptr<GameClock> gameClock ) const;

   std::shared_ptr<std::vector<Linedef>> LoadLinedefs() const;
   BspNode* LoadBspTree() const;
};

NAMESPACE_END
