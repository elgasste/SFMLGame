#pragma once

#include "Common.h"
#include "IGameStateInputHandler.h"

NAMESPACE_BEGIN

class InputReader;
class GameData;
class Menu;

class MenuStateInputHandler : public IGameStateInputHandler
{
public:
   MenuStateInputHandler( std::shared_ptr<InputReader> inputReader,
                          std::shared_ptr<GameData> gameData,
                          std::shared_ptr<Menu> menu );

   // IGameStateInputHandler
   void HandleInput() override;

private:
   std::shared_ptr<InputReader> _inputReader;
   std::shared_ptr<GameData> _gameData;

   std::shared_ptr<Menu> _menu;
};

NAMESPACE_END
