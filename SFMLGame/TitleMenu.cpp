#include "TitleMenu.h"

using namespace NAMESPACE;
using namespace std;

TitleMenu::TitleMenu( shared_ptr<EventQueue> eventQueue ) :
   Menu( eventQueue )
{
   _options.push_back( { IDS_MenuOptionStartGame, GameEventType::StartGame } );
   _options.push_back( { IDS_MenuOptionQuit, GameEventType::Quit } );
}
