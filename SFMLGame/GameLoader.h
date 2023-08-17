#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class Game;
class GameData;
class GameConfig;
class RenderData;

class GameLoader
{
public:
   std::shared_ptr<Game> Load() const;

private:
   std::shared_ptr<GameData> LoadGameData( std::shared_ptr<GameConfig> gameConfig ) const;
   std::shared_ptr<RenderData> LoadRenderData() const;
};

NAMESPACE_END
