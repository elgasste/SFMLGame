#pragma once

#include "Common.h"
#include "IGameStateRenderer.h"

NAMESPACE_BEGIN

class PlayingStateRenderer : public IGameStateRenderer
{
public:
   // IGameStateRenderer
   void Render() override;
};

NAMESPACE_END
