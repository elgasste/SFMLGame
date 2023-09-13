#include "PlayingStateRenderer.h"
#include "RenderConfig.h"
#include "RenderData.h"
#include "GameConfig.h"
#include "GameData.h"
#include "SFMLWindow.h"
#include "Entity.h"
#include "EntitySprite.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

PlayingStateRenderer::PlayingStateRenderer( shared_ptr<RenderConfig> renderConfig,
                                            shared_ptr<RenderData> renderData,
                                            shared_ptr<GameConfig> gameConfig,
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

   _linesegVertexArray = VertexArray( LineStrip, 2 );
   _linesegVertexArray[0].color = Color::White;
   _linesegVertexArray[1].color = Color::White;

   _playerHitBoxRect.setFillColor( Color::Red );
}

void PlayingStateRenderer::Render()
{
   RenderLinesegsRecursive( _gameData->GetRootBspNode() );

   auto player = _gameData->GetPlayer();
   auto& playerPosition = player->GetPosition();
   auto& playerHitBoxOffset = player->GetHitBoxOffset();

   _playerHitBoxRect.setPosition( playerPosition.x + playerHitBoxOffset.x, playerPosition.y + playerHitBoxOffset.y );
   _playerHitBoxRect.setSize( player->GetHitBoxSize() );

   _window->Draw( _playerHitBoxRect );

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

void PlayingStateRenderer::RenderLinesegsRecursive( BspNode* node )
{
   if ( !node )
   {
      return;
   }
   else if ( node->isLeaf )
   {
      for ( auto& lineseg : node->subSector->lineSegs )
      {
         _linesegVertexArray[0].position = lineseg.start;
         _linesegVertexArray[1].position = lineseg.end;
         _window->Draw( _linesegVertexArray );
      }
   }
   else
   {
      RenderLinesegsRecursive( node->leftChild );
      RenderLinesegsRecursive( node->rightChild );
   }
}
