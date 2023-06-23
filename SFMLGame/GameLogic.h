#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class InputHandler;

class GameLogic
{
public:
   GameLogic( std::shared_ptr<InputHandler> inputHandler );

   void Tick();

private:
   std::shared_ptr<InputHandler> _inputHandler;
};

NAMESPACE_END
