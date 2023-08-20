#pragma once

#include "Common.h"
#include "GameRunningTracker.h"

NAMESPACE_BEGIN

class GameData;
class GameClock;
class InputReader;
class GameLogic;
class GameRenderer;

class Game
{
public:
   Game( std::shared_ptr<GameData> gameData,
         std::shared_ptr<GameClock> clock,
         std::shared_ptr<InputReader> inputReader,
         std::shared_ptr<GameLogic> logic,
         std::shared_ptr<GameRenderer> renderer,
         std::shared_ptr<GameRunningTracker> gameRunningTracker );

   void Run();

private:
   std::shared_ptr<GameData> _gameData;
   std::shared_ptr<GameClock> _clock;
   std::shared_ptr<InputReader> _inputReader;
   std::shared_ptr<GameLogic> _logic;
   std::shared_ptr<GameRenderer> _renderer;
   std::shared_ptr<GameRunningTracker> _gameRunningTracker;
};

NAMESPACE_END
