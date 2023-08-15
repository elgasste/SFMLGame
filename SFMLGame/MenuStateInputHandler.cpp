#include "MenuStateInputHandler.h"
#include "InputReader.h"
#include "GameData.h"
#include "Menu.h"

using namespace NAMESPACE;
using namespace std;

MenuStateInputHandler::MenuStateInputHandler( shared_ptr<InputReader> inputReader,
                                              shared_ptr<GameData> gameData,
                                              shared_ptr<Menu> menu ) :
   _inputReader( inputReader ),
   _gameData( gameData ),
   _menu( menu )
{
}

void MenuStateInputHandler::HandleInput()
{
   if ( _inputReader->WasButtonPressed( Button::Back ) )
   {
      _gameData->SetGameState( GameState::Playing );
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
