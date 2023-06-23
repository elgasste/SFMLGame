#pragma once

#include "Common.h"
#include "IEventListener.h"
#include "IGameStateController.h"
#include "GameEvent.h"

NAMESPACE_BEGIN

class EventAggregator;
class GameClock;
class IInputReader;
class GameLogic;
class GameRenderer;

class Game : public IEventListener,
             public IGameStateController
{
public:
   Game( std::shared_ptr<EventAggregator> eventAggregator,
         std::shared_ptr<GameClock> clock,
         std::shared_ptr<IInputReader> inputReader,
         std::shared_ptr<GameLogic> logic,
         std::shared_ptr<GameRenderer> renderer );

   void Run();

   // IEventListener
   void HandleEvent( GameEvent event ) override;

   // IGameStateController
   GameState GetState() const { return _state; }
   void SetState( GameState state ) { _state = state; }

private:
   std::shared_ptr<EventAggregator> _eventAggregator;
   std::shared_ptr<GameClock> _clock;
   std::shared_ptr<IInputReader> _inputReader;
   std::shared_ptr<GameLogic> _logic;
   std::shared_ptr<GameRenderer> _renderer;

   GameState _state;
   bool _isRunning;
};

NAMESPACE_END
