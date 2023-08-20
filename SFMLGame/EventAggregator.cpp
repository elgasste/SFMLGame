#include "EventAggregator.h"

using namespace NAMESPACE;
using namespace std;

void EventAggregator::PushEvent( GameEvent event )
{
   _eventQueue.push( event );
}

GameEvent EventAggregator::GetNextEvent()
{
   auto nextEvent = _eventQueue.front();
   _eventQueue.pop();

   return nextEvent;
}

void EventAggregator::Flush()
{
   while ( !_eventQueue.empty() )
   {
      _eventQueue.pop();
   }
}
