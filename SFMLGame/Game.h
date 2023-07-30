#pragma once

#include "Common.h"
#include "IEventListener.h"
#include "GameEvent.h"

NAMESPACE_BEGIN

class GameData;
class EventAggregator;
class GameClock;
class InputReader;
class GameLogic;
class GameRenderer;

class Game : public IEventListener
{
public:
   Game( std::shared_ptr<GameData> gameData,
         std::shared_ptr<EventAggregator> eventAggregator,
         std::shared_ptr<GameClock> clock,
         std::shared_ptr<InputReader> inputReader,
         std::shared_ptr<GameLogic> logic,
         std::shared_ptr<GameRenderer> renderer );

   void Run();

   // IEventListener
   void HandleEvent( GameEvent event ) override;

private:
   std::shared_ptr<GameData> _gameData;
   std::shared_ptr<EventAggregator> _eventAggregator;
   std::shared_ptr<GameClock> _clock;
   std::shared_ptr<InputReader> _inputReader;
   std::shared_ptr<GameLogic> _logic;
   std::shared_ptr<GameRenderer> _renderer;

   bool _isRunning;
};

NAMESPACE_END
