#pragma once

#include "Common.h"
#include "GameEvent.h"

NAMESPACE_BEGIN

class __declspec( novtable ) IEventListener
{
public:
   virtual void HandleEvent( GameEvent event ) = 0;
};

NAMESPACE_END
