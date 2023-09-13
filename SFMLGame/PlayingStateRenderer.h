#pragma once

#include "Common.h"
#include "IGameStateRenderer.h"
#include "EntitySpriteLayer.h"
#include "BspNode.h"

NAMESPACE_BEGIN

class RenderConfig;
class RenderData;
class GameConfig;
class GameData;
class SFMLWindow;

class PlayingStateRenderer : public IGameStateRenderer
{
public:
   PlayingStateRenderer( std::shared_ptr<RenderConfig> renderConfig,
                         std::shared_ptr<RenderData> renderData,
                         std::shared_ptr<GameConfig> gameConfig,
                         std::shared_ptr<GameData> gameData,
                         std::shared_ptr<SFMLWindow> window );

   // IGameStateRenderer
   void Render() override;

private:
   void RenderLinesegsRecursive( BspNode* node );

private:
   std::shared_ptr<RenderData> _renderData;
   std::shared_ptr<GameData> _gameData;
   std::shared_ptr<SFMLWindow> _window;

   std::vector<EntitySpriteLayer> _entitySpriteLayerOrder;

   sf::VertexArray _linesegVertexArray;
   sf::RectangleShape _playerHitBoxRect;
};

NAMESPACE_END
