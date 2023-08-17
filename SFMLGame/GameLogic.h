#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class GameData;
class RenderConfig;
class GameInputHandler;
class GameClock;

class GameLogic
{
public:
   GameLogic( std::shared_ptr<GameData> gameData,
              std::shared_ptr<RenderConfig> renderConfig,
              std::shared_ptr<GameInputHandler> inputHandler,
              std::shared_ptr<GameClock> clock );

   void Tick();

private:
   void UpdateBallPosition() const;
   void ClipBall() const;

private:
   std::shared_ptr<GameData> _gameData;
   std::shared_ptr<RenderConfig> _renderConfig;
   std::shared_ptr<GameInputHandler> _inputHandler;
   std::shared_ptr<GameClock> _clock;
};

NAMESPACE_END
