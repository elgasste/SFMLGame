#include <SFML/Graphics.hpp>

#include "ArenaRenderer.h"
#include "RenderData.h"
#include "SFMLWindow.h"
#include "GameClock.h"
#include "Arena.h"
#include "ActorSprite.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

ArenaRenderer::ArenaRenderer( shared_ptr<RenderData> renderData,
                              shared_ptr<SFMLWindow> window,
                              shared_ptr<GameClock> clock,
                              shared_ptr<Arena> arena ) :
   _renderData( renderData ),
   _window( window ),
   _clock( clock ),
   _arena( arena )
{
   // MUFFINS: this data will be part of the EntitySprite class as well
   _playerSpriteFrame = 0;
   _elapsedMovementSeconds = 0;
}

void ArenaRenderer::Render()
{
   _renderData->PlayerSprite->Tick();

   _window->Draw( _renderData->PlayerSprite->GetSprite() );
}
