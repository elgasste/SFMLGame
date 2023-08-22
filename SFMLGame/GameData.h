#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class Entity;

class GameData
{
public:
   GameData( std::shared_ptr<Entity> ball );

   std::shared_ptr<Entity> GetBall() const { return _ball; }

private:
   std::shared_ptr<Entity> _ball;
};

NAMESPACE_END
