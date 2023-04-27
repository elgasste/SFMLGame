#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class RenderData;
class SFMLWindow;

class ArenaRenderer
{
public:
   ArenaRenderer( std::shared_ptr<RenderData> renderData,
                  std::shared_ptr<SFMLWindow> window );

   void Render();

private:
   std::shared_ptr<RenderData> _renderData;
   std::shared_ptr<SFMLWindow> _window;
};

NAMESPACE_END
