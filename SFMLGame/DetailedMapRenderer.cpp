#include "DetailedMapRenderer.h"
#include "RenderData.h"
#include "GameData.h"
#include "TileRenderMap.h"
#include "SFMLWindow.h"
#include "Entity.h"
#include "EntitySprite.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

DetailedMapRenderer::DetailedMapRenderer( shared_ptr<RenderData> renderData,
                                          shared_ptr<GameData> gameData,
                                          shared_ptr<TileRenderMap> tileRenderMap,
                                          shared_ptr<SFMLWindow> window ) :
   _renderData( renderData ),
   _gameData( gameData ),
   _tileRenderMap( tileRenderMap ),
   _window( window )
{
   _entitySpriteLayerOrder =
   {
      EntitySpriteLayer::Body,
      EntitySpriteLayer::Legs,
      EntitySpriteLayer::Torso,
      EntitySpriteLayer::Belt,
      EntitySpriteLayer::Feet,
      EntitySpriteLayer::Head,
      EntitySpriteLayer::Hands
   };
}

void DetailedMapRenderer::Render()
{
   // rear tiles first
   DrawTiles( true );

   // then the player
   auto playerSprite = _renderData->GetPlayerSprite();
   playerSprite->Tick();
   playerSprite->SetPosition( _gameData->GetPlayer()->GetPosition() );

   for ( auto layer : _entitySpriteLayerOrder )
   {
      if ( playerSprite->HasLayer( layer ) )
      {
         _window->Draw( playerSprite->GetSpriteForLayer( layer ) );
      }
   }

   // then front tiles
   DrawTiles( false );
}

void DetailedMapRenderer::DrawTiles( bool rearTiles ) const
{
   auto tileSize = _tileRenderMap->GetTileSize();
   auto& mapSize = _tileRenderMap->GetMapSize();

   for ( int i = 0; i < mapSize.x; i++ )
   {
      for ( int j = 0; j < mapSize.y; j++ )
      {
         auto tileIndex = _tileRenderMap->GetTileIndex( i, j, rearTiles );

         if ( tileIndex >= 0 )
         {
            auto positionX = (float)( i * tileSize );
            auto positionY = (float)( j * tileSize );
            _window->Draw( _tileRenderMap->GetTileSprite( tileIndex, positionX, positionY ) );
         }
      }
   }
}
