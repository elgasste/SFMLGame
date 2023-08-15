#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class GameConfig;
class GameData;
class GameClock;
class GameInputHandler;
class BspOperator;
class Entity;

class GameLogic
{
public:
   GameLogic( std::shared_ptr<GameConfig> gameConfig,
              std::shared_ptr<GameData> gameData,
              std::shared_ptr<GameClock> clock,
              std::shared_ptr<GameInputHandler> inputHandler,
              std::shared_ptr<BspOperator> bspOperator );

   void Tick();

private:
   void MovePlayer() const;
   bool EntityCollidedWithWall( std::shared_ptr<Entity> entity, float xDest, float yDest ) const;
   void DeceleratePlayer( std::shared_ptr<Entity> player, bool collidedWithWall ) const;

private:
   std::shared_ptr<GameConfig> _gameConfig;
   std::shared_ptr<GameData> _gameData;
   std::shared_ptr<GameClock> _clock;
   std::shared_ptr<GameInputHandler> _inputHandler;
   std::shared_ptr<BspOperator> _bspOperator;
};

NAMESPACE_END
