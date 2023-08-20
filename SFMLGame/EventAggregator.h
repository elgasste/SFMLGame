#pragma once

#include "Common.h"
#include "GameEvent.h"

NAMESPACE_BEGIN

class IEventListener;

class EventAggregator
{
public:
   void AddListener( GameEvent event, IEventListener* listener );
   void RaiseEvent( GameEvent event ) const;

   bool HasEvents() { return !_eventQueue.empty(); }
   void PushEvent( GameEvent event );
   GameEvent GetNextEvent();
   void Flush();

private:
   std::map<GameEvent, std::vector<IEventListener*>> _listenersMap;
   std::queue<GameEvent> _eventQueue;
};

NAMESPACE_END
