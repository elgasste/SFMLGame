#pragma once

#include "Common.h"
#include "IGameStateInputHandler.h"

NAMESPACE_BEGIN

class IInputReader;

class MenuStateInputHandler : public IGameStateInputHandler
{
public:
   MenuStateInputHandler( std::shared_ptr<IInputReader> inputReader );

   // IGameStateInputHandler
   void HandleInput() override;

private:
   std::shared_ptr<IInputReader> _inputReader;
};

NAMESPACE_END
