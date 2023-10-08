#pragma once

#include "Common.h"
#include "GameRunningTracker.h"
#include "GameStateTracker.h"

NAMESPACE_BEGIN

class GameClock;
class InputHandler;
class GameLogic;
class SFMLWindow;
class GameRenderer;

class Game
{
public:
   Game( std::shared_ptr<GameClock> clock,
         std::shared_ptr<InputHandler> inputHandler,
         std::shared_ptr<GameLogic> logic,
         std::shared_ptr<SFMLWindow> window,
         std::shared_ptr<GameRenderer> renderer,
         std::shared_ptr<GameRunningTracker> gameRunningTracker,
         std::shared_ptr<GameStateTracker> gameStateTracker );

   void Run();

private:
   std::shared_ptr<GameClock> _clock;
   std::shared_ptr<InputHandler> _inputHandler;
   std::shared_ptr<GameLogic> _logic;
   std::shared_ptr<SFMLWindow> _window;
   std::shared_ptr<GameRenderer> _renderer;
   std::shared_ptr<GameRunningTracker> _gameRunningTracker;
   std::shared_ptr<GameStateTracker> _gameStateTracker;
};

NAMESPACE_END
