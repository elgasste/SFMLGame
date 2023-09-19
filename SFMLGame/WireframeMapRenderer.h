#pragma once

#include "Common.h"
#include "BspNode.h"

NAMESPACE_BEGIN

class RenderConfig;
class GameData;
class SFMLWindow;

class WireframeMapRenderer
{
public:
   WireframeMapRenderer( std::shared_ptr<RenderConfig> renderConfig,
                         std::shared_ptr<GameData> gameData,
                         std::shared_ptr<SFMLWindow> window );

   void Render();

private:
   void RenderLinesegsRecursive( BspNode* node );

private:
   std::shared_ptr<GameData> _gameData;
   std::shared_ptr<SFMLWindow> _window;

   sf::VertexArray _linesegVertexArray;
   sf::RectangleShape _playerHitBoxRect;
   sf::Vector2f _playerHitBoxRectPosition;
   sf::Vector2f _playerHitBoxRectSize;
};

NAMESPACE_END
