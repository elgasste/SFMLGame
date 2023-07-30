#pragma once

#include "Common.h"
#include "IGameStateInputHandler.h"

NAMESPACE_BEGIN

class InputReader;
class GameStateController;
class Entity;
class BspRunner;

class PlayingStateInputHandler : public IGameStateInputHandler
{
public:
   PlayingStateInputHandler( std::shared_ptr<InputReader> inputReader,
                             std::shared_ptr<GameStateController> stateController,
                             std::shared_ptr<Entity> player,
                             std::shared_ptr<BspRunner> bspRunner );

   // IGameStateInputHandler
   void HandleInput() override;

private:
   std::shared_ptr<InputReader> _inputReader;
   std::shared_ptr<GameStateController> _stateController;
   std::shared_ptr<Entity> _player;
   std::shared_ptr<BspRunner> _bspRunner;
};

NAMESPACE_END
