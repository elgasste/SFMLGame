#pragma once

#include "Common.h"
#include "IGameStateInputHandler.h"

NAMESPACE_BEGIN

class IInputReader;
class GameStateController;

class PlayingStateInputHandler : public IGameStateInputHandler
{
public:
   PlayingStateInputHandler( std::shared_ptr<IInputReader> inputReader,
                             std::shared_ptr<GameStateController> stateController );

   // IGameStateInputHandler
   void HandleInput() override;

private:
   std::shared_ptr<IInputReader> _inputReader;
   std::shared_ptr<GameStateController> _stateController;
};

NAMESPACE_END
