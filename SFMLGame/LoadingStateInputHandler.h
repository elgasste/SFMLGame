#pragma once

#include "Common.h"
#include "IGameStateInputHandler.h"

NAMESPACE_BEGIN

class LoadingStateInputHandler : public IGameStateInputHandler
{
public:
   void HandleInput() override { }
};

NAMESPACE_END
