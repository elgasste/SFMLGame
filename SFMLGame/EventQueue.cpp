#include "EventQueue.h"

using namespace NAMESPACE;
using namespace std;

void EventQueue::Push( GameEventType type, std::shared_ptr<IGameEventArgs> args )
{
   _eventQueue.push( { type, args } );
}

void EventQueue::Push( GameEventType type )
{
   Push( type, nullptr );
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
