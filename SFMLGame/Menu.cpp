#include "Menu.h"
#include "EventQueue.h"

using namespace NAMESPACE;
using namespace std;

Menu::Menu( shared_ptr<EventQueue> eventQueue ) :
   _eventQueue( eventQueue ),
   _currentOptionIndex( 0 )
{
}

void Menu::ScrollUp()
{
   _currentOptionIndex--;

   if ( _currentOptionIndex < 0 )
   {
      _currentOptionIndex = (int)_options.size() - 1;
   }
}

void Menu::ScrollDown()
{
   _currentOptionIndex++;

   if ( _currentOptionIndex >= (int)_options.size() )
   {
      _currentOptionIndex = 0;
   }
}

void Menu::SelectCurrentOption() const
{
   _eventQueue->Push( _options.at( _currentOptionIndex ).eventType );
}
