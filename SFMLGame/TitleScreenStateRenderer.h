#pragma once

#include "Common.h"
#include "IGameStateRenderer.h"

NAMESPACE_BEGIN

class TitleScreenStateRenderer : public IGameStateRenderer
{
public:
   // IGameStateRenderer
   void Render() override;
};

NAMESPACE_END
