#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class GameInputHandler;

class GameLogic
{
public:
   GameLogic( std::shared_ptr<GameInputHandler> inputHandler );

   void Tick();

private:
   std::shared_ptr<GameInputHandler> _inputHandler;
};

NAMESPACE_END
