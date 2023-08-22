#pragma once

#include "Common.h"
#include "GameRunningTracker.h"
#include "GameStateTracker.h"

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
              std::shared_ptr<GameRunningTracker> gameRunningTracker,
              std::shared_ptr<GameStateTracker> gameStateTracker );

   void Tick();

private:
   void HandleEvents();
   void OnQuit() const;
   void OnOpenMenu() const;
   void OnCloseMenu() const;
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
   std::shared_ptr<GameStateTracker> _gameStateTracker;
};

NAMESPACE_END
