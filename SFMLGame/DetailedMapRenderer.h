#pragma once

#include "Common.h"
#include "EntitySpriteLayer.h"

NAMESPACE_BEGIN

class RenderData;
class GameData;
class SFMLWindow;

class DetailedMapRenderer
{
public:
   DetailedMapRenderer( std::shared_ptr<RenderData> renderData,
                        std::shared_ptr<GameData> gameData,
                        std::shared_ptr<SFMLWindow> window );

   void Render();

private:
   std::shared_ptr<RenderData> _renderData;
   std::shared_ptr<GameData> _gameData;
   std::shared_ptr<SFMLWindow> _window;

   std::vector<EntitySpriteLayer> _entitySpriteLayerOrder;
};

NAMESPACE_END
