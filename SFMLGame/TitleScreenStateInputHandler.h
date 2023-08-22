#pragma once

#include "Common.h"
#include "IGameStateInputHandler.h"

NAMESPACE_BEGIN

class TitleScreenStateInputHandler : public IGameStateInputHandler
{
public:
   // IGameStateInputHandler
   void HandleInput() override;
};

NAMESPACE_END
