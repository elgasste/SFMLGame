#pragma once

#include "Common.h"
#include "IGameStateInputHandler.h"

NAMESPACE_BEGIN

class InputStateController;
class GameConfig;
class EventQueue;

class PlayingStateInputHandler : public IGameStateInputHandler
{
public:
   PlayingStateInputHandler( std::shared_ptr<InputStateController> inputReader,
                             std::shared_ptr<GameConfig> gameConfig,
                             std::shared_ptr<EventQueue> eventQueue );

   // IGameStateInputHandler
   void HandleInput() override;

private:
   std::shared_ptr<InputStateController> _inputReader;
   std::shared_ptr<GameConfig> _gameConfig;
   std::shared_ptr<EventQueue> _eventQueue;
};

NAMESPACE_END
