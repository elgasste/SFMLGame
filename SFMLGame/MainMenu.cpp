#include "MainMenu.h"

using namespace NAMESPACE;
using namespace std;

MainMenu::MainMenu( shared_ptr<EventQueue> eventQueue) :
   Menu( eventQueue )
{
   _options.push_back( { IDS_MenuOptionBack, GameEventType::CloseMenu } );
   _options.push_back( { IDS_MenuOptionExitToTitle, GameEventType::ExitToTitle } );
   _options.push_back( { IDS_MenuOptionQuit, GameEventType::Quit } );
}
