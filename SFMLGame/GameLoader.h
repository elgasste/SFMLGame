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

   std::shared_ptr<std::vector<LineDef>> LoadLinedefs() const;
   std::shared_ptr<std::vector<SubSector>> LoadSubSectors( std::shared_ptr<std::vector<LineDef>> linedefs) const;
   BspNode* LoadBspTree( std::shared_ptr<std::vector<LineDef>> linedefs,
                         std::shared_ptr<std::vector<SubSector>> subSectors ) const;
};

NAMESPACE_END
