#pragma once

#include "Common.h"
#include "GameEvent.h"

NAMESPACE_BEGIN

class IGameEventArgs;

class EventQueue
{
public:
   bool HasEvents() { return !_eventQueue.empty(); }
   void Push( GameEventType type, std::shared_ptr<IGameEventArgs> args );
   void Push( GameEventType type );
   GameEvent GetNext();
   void Flush();

private:
   std::queue<GameEvent> _eventQueue;
};

NAMESPACE_END
