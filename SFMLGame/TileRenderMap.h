#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class TileRenderMap
{
public:
   TileRenderMap();

   int GetTileSize() { return _tileSize; }
   const sf::Vector2i& GetMapSize() { return _mapSize; }
   const sf::Sprite& GetTileSprite( int mapX, int mapY, float positionX, float positionY );

private:
   void LoadTestMap();

private:
   sf::Texture _tileSetTexture;
   sf::Vector2i _tileSetSize;
   int _tileSize;

   sf::Vector2i _mapSize;
   std::vector<int> _mapTileIndexes;

   sf::Sprite _tileSprite;
   sf::IntRect _tileSpriteTextureRect;
   sf::Vector2f _tileSpritePosition;
};

NAMESPACE_END
