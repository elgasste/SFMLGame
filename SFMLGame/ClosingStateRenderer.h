#pragma once

#include "Common.h"
#include "IGameStateRenderer.h"

NAMESPACE_BEGIN

class ClosingStateRenderer : public IGameStateRenderer
{
public:
   // IGameStateRenderer
   void Render() override { }
};

NAMESPACE_END
