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

private:
   std::map<GameEvent, std::vector<IEventListener*>> _listenersMap;
};

NAMESPACE_END
