#include "MenuStateInputHandler.h"
#include "IInputReader.h"
#include "GameStateController.h"
#include "Menu.h"

using namespace NAMESPACE;
using namespace std;

MenuStateInputHandler::MenuStateInputHandler( shared_ptr<IInputReader> inputReader,
                                              shared_ptr<GameStateController> stateController,
                                              shared_ptr<Menu> menu ) :
   _inputReader( inputReader ),
   _stateController( stateController ),
   _menu( menu )
{
}

void MenuStateInputHandler::HandleInput()
{
   if ( _inputReader->WasButtonPressed( Button::Back ) )
   {
      _stateController->SetState( GameState::Playing );
   }
   else if ( _inputReader->WasButtonPressed( Button::Up ) )
   {
      _menu->ScrollUp();
   }
   else if ( _inputReader->WasButtonPressed( Button::Down ) )
   {
      _menu->ScrollDown();
   }
   else if ( _inputReader->WasButtonPressed( Button::Action ) )
   {
      _menu->SelectCurrentOption();
   }
}
