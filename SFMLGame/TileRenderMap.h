#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class TileRenderMap
{
public:
   TileRenderMap();

   int GetTileSize() { return _tileSize; }
   const sf::Vector2i& GetMapSize() { return _mapSize; }
   int GetTileIndex( int mapX, int mapY, bool rearTile ) const;
   const sf::Sprite& GetTileSprite( int tileIndex, float positionX, float positionY );

private:
   void LoadTestMap();

private:
   sf::Texture _tileSetTexture;
   sf::Vector2i _tileSetSize;
   int _tileSize;

   sf::Vector2i _mapSize;
   std::vector<int> _rearMapTileIndexes;
   std::vector<int> _frontMapTileIndexes;

   sf::Sprite _tileSprite;
   sf::IntRect _tileSpriteTextureRect;
   sf::Vector2f _tileSpritePosition;
};

NAMESPACE_END
