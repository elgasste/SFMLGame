#include "DetailedMapRenderer.h"
#include "RenderData.h"
#include "GameData.h"
#include "SFMLWindow.h"
#include "Entity.h"
#include "EntitySprite.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

DetailedMapRenderer::DetailedMapRenderer( shared_ptr<RenderData> renderData,
                                          shared_ptr<GameData> gameData,
                                          shared_ptr<SFMLWindow> window ) :
   _renderData( renderData ),
   _gameData( gameData ),
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
}
