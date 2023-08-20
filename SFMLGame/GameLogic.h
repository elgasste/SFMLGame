#pragma once

#include "Common.h"
#include "GameRunningTracker.h"

NAMESPACE_BEGIN

class GameConfig;
class GameData;
class RenderConfig;
class GameInputHandler;
class EventQueue;
class GameClock;
class IGameEventArgs;

class GameLogic
{
public:
   GameLogic( std::shared_ptr<GameConfig> gameConfig,
              std::shared_ptr<GameData> gameData,
              std::shared_ptr<RenderConfig> renderConfig,
              std::shared_ptr<GameInputHandler> inputHandler,
              std::shared_ptr<EventQueue> eventQueue,
              std::shared_ptr<GameClock> clock,
              std::shared_ptr<GameRunningTracker> gameRunningTracker );

   void Tick();

private:
   void HandleEvents();
   void OnChangeGameState( std::shared_ptr<IGameEventArgs> args ) const;
   void OnTurnBall( std::shared_ptr<IGameEventArgs> args ) const;
   void OnPushBall( std::shared_ptr<IGameEventArgs> args ) const;

   void UpdateBallPosition() const;
   void ClipBall() const;

private:
   std::shared_ptr<GameConfig> _gameConfig;
   std::shared_ptr<GameData> _gameData;
   std::shared_ptr<RenderConfig> _renderConfig;
   std::shared_ptr<GameInputHandler> _inputHandler;
   std::shared_ptr<EventQueue> _eventQueue;
   std::shared_ptr<GameClock> _clock;
   std::shared_ptr<GameRunningTracker> _gameRunningTracker;
};

NAMESPACE_END
