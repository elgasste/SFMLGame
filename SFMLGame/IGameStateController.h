#pragma once

#include "Common.h"
#include "GameState.h"

NAMESPACE_BEGIN

class __declspec( novtable ) IGameStateController
{
public:
   virtual GameState GetState() const = 0;
   virtual void SetState( GameState state ) = 0;
};

NAMESPACE_END
