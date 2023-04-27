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
                              shared_ptr<SFMLWindow> window ) :
   _renderData( renderData ),
   _window( window )
{
}

void ArenaRenderer::Render()
{
   _renderData->PlayerSprite->Tick();

   _window->Draw( _renderData->PlayerSprite->GetSprite() );
}
