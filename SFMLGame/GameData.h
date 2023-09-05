#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class Entity;

class GameData
{
public:
   GameData( std::shared_ptr<Entity> player );

   std::shared_ptr<Entity> GetPlayer() const { return _player; }

private:
   std::shared_ptr<Entity> _player;
};

NAMESPACE_END
