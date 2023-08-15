#pragma once

#include "Common.h"
#include "IGameStateInputHandler.h"

NAMESPACE_BEGIN

class GameConfig;
class GameData;
class GameClock;
class InputReader;
class GameStateController;

class PlayingStateInputHandler : public IGameStateInputHandler
{
public:
   PlayingStateInputHandler( std::shared_ptr<GameConfig> gameConfig,
                             std::shared_ptr<GameData> gameData,
                             std::shared_ptr<GameClock> clock,
                             std::shared_ptr<InputReader> inputReader,
                             std::shared_ptr<GameStateController> stateController );

   void HandleInput() override;

private:
   void HandlePlayerTurning() const;
   void HandlePlayerMovement() const;

private:
   std::shared_ptr<GameConfig> _gameConfig;
   std::shared_ptr<GameData> _gameData;
   std::shared_ptr<GameClock> _clock;
   std::shared_ptr<InputReader> _inputReader;
   std::shared_ptr<GameStateController> _stateController;
};

NAMESPACE_END
