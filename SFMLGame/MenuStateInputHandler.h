#pragma once

#include "Common.h"
#include "IGameStateInputHandler.h"

NAMESPACE_BEGIN

class InputReader;
class GameStateController;
class Menu;

class MenuStateInputHandler : public IGameStateInputHandler
{
public:
   MenuStateInputHandler( std::shared_ptr<InputReader> inputReader,
                          std::shared_ptr<GameStateController> stateController,
                          std::shared_ptr<Menu> menu );

   // IGameStateInputHandler
   void HandleInput() override;

private:
   std::shared_ptr<InputReader> _inputReader;
   std::shared_ptr<GameStateController> _stateController;

   std::shared_ptr<Menu> _menu;
};

NAMESPACE_END
