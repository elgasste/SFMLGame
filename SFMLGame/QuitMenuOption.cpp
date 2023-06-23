#include "QuitMenuOption.h"
#include "EventAggregator.h"

using namespace NAMESPACE;
using namespace std;

QuitMenuOption::QuitMenuOption( shared_ptr<EventAggregator> eventAggregator ) :
   _eventAggregator( eventAggregator ),
   _text( "Quit" )
{
}

void QuitMenuOption::Select()
{
   _eventAggregator->RaiseEvent( GameEvent::Quit );
}
