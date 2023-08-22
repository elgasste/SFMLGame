#pragma once

#include "Common.h"
#include "IGameStateRenderer.h"

NAMESPACE_BEGIN

class TitleMenuStateRenderer : public IGameStateRenderer
{
public:
   // IGameStateRenderer
   void Render() override;
};

NAMESPACE_END
