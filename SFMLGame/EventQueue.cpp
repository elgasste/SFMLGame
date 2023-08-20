#include "EventQueue.h"

using namespace NAMESPACE;
using namespace std;

void EventQueue::Push( GameEvent event )
{
   _eventQueue.push( event );
}

GameEvent EventQueue::GetNext()
{
   auto nextEvent = _eventQueue.front();
   _eventQueue.pop();

   return nextEvent;
}

void EventQueue::Flush()
{
   while ( !_eventQueue.empty() )
   {
      _eventQueue.pop();
   }
}
