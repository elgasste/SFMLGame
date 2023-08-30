#pragma once

#include "Common.h"
#include "BspNode.h"

NAMESPACE_BEGIN

class GameData;

class CollisionDetector
{
public:
   CollisionDetector( std::shared_ptr<GameData> gameData );

   bool CheckWallCollision( float startX, float startY, float endX, float endY, Lineseg& collidingLineseg ) const;

private:
   bool CheckWallNodeCollisionRecursive( BspNode* node, float startX, float startY, float endX, float endY, Lineseg& collidingLineseg ) const;

private:
   std::shared_ptr<GameData> _gameData;
};

NAMESPACE_END
