#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class GameInputHandler;
class Entity;

class GameLogic
{
public:
   GameLogic( std::shared_ptr<GameInputHandler> inputHandler,
              std::shared_ptr<Entity> player );

   void Tick();

private:
   std::shared_ptr<GameInputHandler> _inputHandler;
   std::shared_ptr<Entity> _player;
};

NAMESPACE_END
