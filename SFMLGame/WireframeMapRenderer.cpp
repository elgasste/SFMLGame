#include "WireframeMapRenderer.h"
#include "RenderConfig.h"
#include "GameData.h"
#include "SFMLWindow.h"
#include "Entity.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

WireframeMapRenderer::WireframeMapRenderer( shared_ptr<RenderConfig> renderConfig,
                                            shared_ptr<GameData> gameData,
                                            shared_ptr<SFMLWindow> window ) :
   _gameData( gameData ),
   _window( window )
{
   _linesegVertexArray = VertexArray( LineStrip, 2 );
   _linesegVertexArray[0].color = renderConfig->WireframeLinedefColor;
   _linesegVertexArray[1].color = renderConfig->WireframeLinedefColor;

   _playerHitBoxRect = RectangleShape();
   _playerHitBoxRect.setFillColor( renderConfig->WireframePlayerHitBoxFillColor );
   _playerHitBoxRectPosition = Vector2f();
   _playerHitBoxRectSize = Vector2f();
}

void WireframeMapRenderer::Render()
{
   RenderLinesegsRecursive( _gameData->GetRootBspNode() );

   auto player = _gameData->GetPlayer();
   auto& playerPosition = player->GetPosition();
   auto& playerHitBoxSize = player->GetHitBoxSize();
   auto& playerHitBoxOffset = player->GetHitBoxOffset();

   _playerHitBoxRectPosition.x = playerPosition.x + playerHitBoxOffset.x;
   _playerHitBoxRectPosition.y = playerPosition.y + playerHitBoxOffset.y;
   _playerHitBoxRect.setPosition( _playerHitBoxRectPosition );

   _playerHitBoxRectSize.x = playerHitBoxSize.x;
   _playerHitBoxRectSize.y = playerHitBoxSize.y;
   _playerHitBoxRect.setSize( _playerHitBoxRectSize );

   _window->Draw( _playerHitBoxRect );
}

// TODO: performance could take a major hit if this is a huge map,
// maybe we can find a way to only draw visible linedefs?
void WireframeMapRenderer::RenderLinesegsRecursive( BspNode* node )
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
