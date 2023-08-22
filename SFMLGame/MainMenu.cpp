#include "MainMenu.h"
#include "EventQueue.h"

using namespace NAMESPACE;
using namespace std;

MainMenu::MainMenu( shared_ptr<EventQueue> eventQueue ) :
   _eventQueue( eventQueue ),
   _currentOptionIndex( 0 )
{
   _options.push_back( { IDS_MenuOptionBack, GameEventType::CloseMenu } );
   _options.push_back( { IDS_MenuOptionQuit, GameEventType::Quit } );
}

void MainMenu::ScrollUp()
{
   _currentOptionIndex--;

   if ( _currentOptionIndex < 0 )
   {
      _currentOptionIndex = (int)_options.size() - 1;
   }
}

void MainMenu::ScrollDown()
{
   _currentOptionIndex++;

   if ( _currentOptionIndex >= (int)_options.size() )
   {
      _currentOptionIndex = 0;
   }
}

void MainMenu::SelectCurrentOption() const
{
   _eventQueue->Push( _options.at( _currentOptionIndex ).eventType );
}
