#pragma once

#include "Common.h"
#include "GameRunningTracker.h"

NAMESPACE_BEGIN

class GameData;
class RenderConfig;
class GameInputHandler;
class EventAggregator;
class GameClock;
class IGameEventArgs;

class GameLogic
{
public:
   GameLogic( std::shared_ptr<GameData> gameData,
              std::shared_ptr<RenderConfig> renderConfig,
              std::shared_ptr<GameInputHandler> inputHandler,
              std::shared_ptr<EventAggregator> eventAggregator,
              std::shared_ptr<GameClock> clock,
              std::shared_ptr<GameRunningTracker> gameRunningTracker );

   void Tick();

private:
   void HandleEvents();
   void UpdateBallPosition() const;
   void ClipBall() const;

   void OnChangeGameState( std::shared_ptr<IGameEventArgs> args );

private:
   std::shared_ptr<GameData> _gameData;
   std::shared_ptr<RenderConfig> _renderConfig;
   std::shared_ptr<GameInputHandler> _inputHandler;
   std::shared_ptr<EventAggregator> _eventAggregator;
   std::shared_ptr<GameClock> _clock;
   std::shared_ptr<GameRunningTracker> _gameRunningTracker;
};

NAMESPACE_END
