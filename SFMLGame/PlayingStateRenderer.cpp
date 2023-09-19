#include "PlayingStateRenderer.h"
#include "GameConfig.h"
#include "WireframeMapRenderer.h"
#include "DetailedMapRenderer.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

PlayingStateRenderer::PlayingStateRenderer( shared_ptr<GameConfig> gameConfig,
                                            shared_ptr<WireframeMapRenderer> wireframeMapRenderer,
                                            shared_ptr<DetailedMapRenderer> detailedMapRenderer ) :
   _gameConfig( gameConfig ),
   _wireframeMapRenderer( wireframeMapRenderer ),
   _detailedMapRenderer( detailedMapRenderer )
{
}

void PlayingStateRenderer::Render()
{
   if ( _gameConfig->ShowWireframeMap )
   {
      _wireframeMapRenderer->Render();
   }
   else
   {
      _detailedMapRenderer->Render();
   }
}
