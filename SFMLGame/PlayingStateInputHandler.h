#pragma once

#include "Common.h"
#include "IGameStateInputHandler.h"

NAMESPACE_BEGIN

class GameConfig;
class InputReader;
class GameStateController;
class Entity;
class BspOperator;

class PlayingStateInputHandler : public IGameStateInputHandler
{
public:
   PlayingStateInputHandler( std::shared_ptr<GameConfig> gameConfig,
                             std::shared_ptr<InputReader> inputReader,
                             std::shared_ptr<GameStateController> stateController,
                             std::shared_ptr<Entity> player,
                             std::shared_ptr<BspOperator> bspOperator );

   // IGameStateInputHandler
   void HandleInput() override;

private:
   std::shared_ptr<GameConfig> _gameConfig;
   std::shared_ptr<InputReader> _inputReader;
   std::shared_ptr<GameStateController> _stateController;
   std::shared_ptr<Entity> _player;
   std::shared_ptr<BspOperator> _bspOperator;
};

NAMESPACE_END
