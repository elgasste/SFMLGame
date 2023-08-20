#pragma once

#include "Common.h"
#include "GameEvent.h"

NAMESPACE_BEGIN

class EventAggregator
{
public:
   bool HasEvents() { return !_eventQueue.empty(); }
   void PushEvent( GameEvent event );
   GameEvent GetNextEvent();
   void Flush();

private:
   std::queue<GameEvent> _eventQueue;
};

NAMESPACE_END
