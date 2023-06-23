#include "MenuStateInputHandler.h"
#include "IInputReader.h"

using namespace NAMESPACE;
using namespace std;

MenuStateInputHandler::MenuStateInputHandler( shared_ptr<IInputReader> inputReader ) :
   _inputReader( inputReader )
{
}

void MenuStateInputHandler::HandleInput()
{
   if ( _inputReader->WasButtonPressed( Button::Back ) )
   {
      // TOOD: go back to Playing state
   }
   else if ( _inputReader->WasButtonPressed( Button::Up ) )
   {
      // TODO: scroll up
   }
   else if ( _inputReader->WasButtonPressed( Button::Down ) )
   {
      // TODO: scroll down
   }
   else if ( _inputReader->WasButtonPressed( Button::Action ) )
   {
      // TODO: select menu option
   }
}
