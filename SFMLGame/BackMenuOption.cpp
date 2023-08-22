#include "BackMenuOption.h"
#include "EventQueue.h"

using namespace NAMESPACE;
using namespace std;

BackMenuOption::BackMenuOption( shared_ptr<EventQueue> eventQueue ) :
   _eventQueue( eventQueue ),
   _text( IDS_MenuOptionBack )
{
}

void BackMenuOption::Select()
{
   _eventQueue->Push( GameEventType::CloseMenu );
}
