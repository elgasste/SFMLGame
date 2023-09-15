#pragma once

#include "Common.h"
#include "Direction.h"
#include "BspNode.h"

NAMESPACE_BEGIN

class GameConfig;
class GameData;
class Entity;

class Collider
{
public:
   Collider( std::shared_ptr<GameConfig> gameConfig,
             std::shared_ptr<GameData> gameData );

   void MoveEntity( std::shared_ptr<Entity> entity, Direction direction, float distance );

private:
   bool HitLinesegRecursive( BspNode* node, float startX, float startY, float endX, float endY, sf::Vector2f& collisionPoint, float& collisionAngle );

private:
   std::shared_ptr<GameConfig> _gameConfig;
   std::shared_ptr<GameData> _gameData;
};

NAMESPACE_END
