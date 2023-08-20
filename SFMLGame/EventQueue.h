#pragma once

#include "Common.h"
#include "GameEvent.h"

NAMESPACE_BEGIN

class EventQueue
{
public:
   bool HasEvents() { return !_eventQueue.empty(); }
   void Push( GameEvent event );
   GameEvent GetNext();
   void Flush();

private:
   std::queue<GameEvent> _eventQueue;
};

NAMESPACE_END
