#include "EventAggregator.h"
#include "IEventListener.h"

using namespace NAMESPACE;
using namespace std;

void EventAggregator::AddListener( GameEvent event, IEventListener* listener )
{
   auto listeners = _listenersMap[event];

   if ( find( listeners.begin(), listeners.end(), listener ) == listeners.end() )
   {
      _listenersMap[event].push_back( listener );
   }
}

void EventAggregator::RaiseEvent( GameEvent event ) const
{
   if ( _listenersMap.count( event ) == 0 )
   {
      return;
   }

   auto& listeners = _listenersMap.at( event );

   for ( auto listener : listeners )
   {
      listener->HandleEvent( event );
   }
}
