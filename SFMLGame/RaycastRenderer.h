#pragma once

#include <SFML/Graphics/Vertex.hpp>

#include "Common.h"
#include "BspNode.h"
#include "PixelColumn.h"

NAMESPACE_BEGIN

class GameConfig;
class GameData;
class RenderConfig;
class RenderData;
class SFMLWindow;
class ColumnTracker;

class RaycastRenderer
{
public:
   RaycastRenderer( std::shared_ptr<GameConfig> gameConfig,
                    std::shared_ptr<GameData> gameData,
                    std::shared_ptr<RenderConfig> renderConfig,
                    std::shared_ptr<RenderData> renderData,
                    std::shared_ptr<SFMLWindow> window,
                    std::shared_ptr<ColumnTracker> columnTracker );
   ~RaycastRenderer();

   void Render();

private:
   void RenderCeilingAndFloor();
   void CheckBspNodeRecursive( BspNode* node );
   void CheckBspLeaf( BspNode* leaf );
   void SetPixelColumnRange( const Lineseg& lineseg, float startAngle, int startPixel, int endPixel );
   void RenderPixelColumns();

private:
   std::shared_ptr<GameConfig> _gameConfig;
   std::shared_ptr<RenderConfig> _renderConfig;
   std::shared_ptr<GameData> _gameData;
   std::shared_ptr<RenderData> _renderData;
   std::shared_ptr<SFMLWindow> _window;
   std::shared_ptr<ColumnTracker> _columnTracker;

   std::vector<PixelColumn> _pixelColumns;

   sf::Vector2f _viewOrigin;
   float _leftFovAngle;

   sf::Vertex* _renderColumns;
   sf::Vertex _floorRenderRect[4];

   sf::Vector2f _skyPosition;
   sf::IntRect _skyTextureRect;
   float _skyTextureScalar;

   sf::Vector2f _spritePosition;
   sf::IntRect _spriteTextureRect;
   sf::Vector2f _spriteVerticalScale;
};

NAMESPACE_END
