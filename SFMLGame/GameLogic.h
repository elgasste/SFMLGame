#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class GameConfig;
class GameData;
class GameInputHandler;
class BspOperator;

class GameLogic
{
public:
   GameLogic( std::shared_ptr<GameConfig> gameConfig,
              std::shared_ptr<GameData> gameData,
              std::shared_ptr<GameInputHandler> inputHandler,
              std::shared_ptr<BspOperator> bspOperator );

   void Tick();

private:
   void MovePlayer();

private:
   std::shared_ptr<GameConfig> _gameConfig;
   std::shared_ptr<GameData> _gameData;
   std::shared_ptr<GameInputHandler> _inputHandler;
   std::shared_ptr<BspOperator> _bspOperator;
};

NAMESPACE_END
