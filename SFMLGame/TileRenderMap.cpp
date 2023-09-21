#include "TileRenderMap.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

TileRenderMap::TileRenderMap()
{
   // MUFFINS: move as much of this as possible to RenderData
   _tileSetTexture = Texture();
   _tileSetTexture.loadFromFile( "Resources/Textures/overworld_tileset.png" );
   _tileSetSize = Vector2i( 16, 10 ); // 512x320 pixels
   _tileSize = 32;

   _mapSize = Vector2i( 30, 20 ); // 960x640 pixels
   _mapTileIndexes = vector<int>( _mapSize.x * _mapSize.y, 0 );

   _tileSprite = Sprite( _tileSetTexture );
   _tileSpriteTextureRect = IntRect( 0, 0, _tileSize, _tileSize );
   _tileSpritePosition = Vector2f( 0, 0 );

   // MUFFINS: this will go in GameLoader eventually
   LoadTestMap();
}

const Sprite& TileRenderMap::GetTileSprite( int mapX, int mapY, float positionX, float positionY )
{
   auto tileIndex = _mapTileIndexes[mapX + ( _mapSize.x * mapY )];
   _tileSpriteTextureRect.left = ( tileIndex % _tileSetSize.x ) * _tileSize;
   _tileSpriteTextureRect.top = ( tileIndex / _tileSetSize.x ) * _tileSize;
   _tileSprite.setTextureRect( _tileSpriteTextureRect );

   _tileSpritePosition.x = positionX;
   _tileSpritePosition.y = positionY;
   _tileSprite.setPosition( _tileSpritePosition );

   return _tileSprite;
}

void TileRenderMap::LoadTestMap()
{
   // 30x20
   _mapTileIndexes = {
       1,  1,  1,  1,  4,  1,  1,  1,  1,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  4,  1,  1,
       1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
       1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  8, 13,  9,  1,  1,  1,
       1,  1,  1,  1,  8, 13, 13, 13, 13, 13, 13,  9,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  8, 34, 7, 14,  1,  1,  1,
       1,  1,  1,  8, 34,  7,  7,  7,  7,  7,  7, 33,  9,  1,  1,  1,  1,  1,  1,  1,  1,  1,  8, 34,  7, 31, 10,  1,  1,  4,
       1,  1,  1, 12,  7,  7,  7,  7,  7,  7,  7,  7, 14,  1,  1,  1,  1,  1,  1,  1,  1,  8, 34,  7, 31, 10,  1,  1,  1,  1,
       1,  1,  1, 11, 32,  7,  7,  7,  7,  7,  7,  7, 14,  1,  1,  1,  1,  1,  1,  1,  1, 12,  7, 31, 10,  1,  1,  1,  1,  1,
       3,  1,  1,  1, 11, 15, 15, 15, 15, 15, 15, 15, 10,  1,  1,  1,  1,  1,  1,  1,  1, 11, 15, 10,  1,  1,  1,  1,  1,  1,
       1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  5,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
       1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  6,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
       1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  6,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
       1,  1,  1,  1,  1,  1,  1,  4,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  6,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
       1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 41, 41, 41, 41, 41, 41, 41,  1,  1,  1,  1,  1,  1,  1,  1,  1,
       1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 42, 40, 40, 40, 40, 40, 42,  1,  1,  1,  1,  1,  1,  1,  1,  1,
       1,  1,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 42,  0,  2,  3,  1,  2, 42,  1,  1,  1,  1,  1,  1,  3,  1,  1,
       1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 42,  1,  3,  0,  3,  0, 42,  1,  1,  1,  1,  1,  1,  1,  1,  1,
       1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 42, 41, 41, 41, 41, 41, 42,  1,  1,  3,  1,  1,  1,  1,  1,  1,
       1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 40, 40, 40, 40, 40, 40, 40,  1,  1,  1,  1,  1,  1,  1,  1,  1,
       1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  6,  1,  1,  1,  1,
       1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  4,  1,  1,  1,  1,  1,  1,  1,  1
   };
}
