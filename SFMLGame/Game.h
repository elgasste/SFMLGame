#pragma once

#include "Common.h"
#include "GameRunningTracker.h"
#include "GameStateTracker.h"

NAMESPACE_BEGIN

class GameClock;
class InputStateController;
class GameInputHandler;
class GameLogic;
class GameRenderer;
class SFMLWindow;

class Game
{
public:
   Game( std::shared_ptr<GameClock> clock,
         std::shared_ptr<InputStateController> inputStateController,
         std::shared_ptr<GameInputHandler> inputHandler,
         std::shared_ptr<GameLogic> logic,
         std::shared_ptr<GameRenderer> renderer,
         std::shared_ptr<SFMLWindow> window,
         std::shared_ptr<GameRunningTracker> gameRunningTracker,
         std::shared_ptr<GameStateTracker> gameStateTracker );

   void Run();

private:
   std::shared_ptr<GameStateTracker> _gameStateTracker;
   std::shared_ptr<GameClock> _clock;
   std::shared_ptr<InputStateController> _inputStateController;
   std::shared_ptr<GameInputHandler> _inputHandler;
   std::shared_ptr<GameLogic> _logic;
   std::shared_ptr<GameRenderer> _renderer;
   std::shared_ptr<SFMLWindow> _window;
   std::shared_ptr<GameRunningTracker> _gameRunningTracker;
};

NAMESPACE_END
