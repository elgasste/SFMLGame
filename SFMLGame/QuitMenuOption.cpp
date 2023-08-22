#include "QuitMenuOption.h"
#include "EventQueue.h"

using namespace NAMESPACE;
using namespace std;

QuitMenuOption::QuitMenuOption( shared_ptr<EventQueue> eventQueue ) :
   _eventQueue( eventQueue ),
   _text( IDS_MenuOptionQuit )
{
}

void QuitMenuOption::Select()
{
   _eventQueue->Push( GameEventType::Quit );
}
