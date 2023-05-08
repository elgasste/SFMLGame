#include <SFML/Graphics.hpp>

#include "PlayingStateRenderer.h"
#include "RenderData.h"
#include "SFMLWindow.h"
#include "GameClock.h"
#include "Arena.h"
#include "EntitySprite.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

PlayingStateRenderer::PlayingStateRenderer( shared_ptr<RenderData> renderData,
                                            shared_ptr<SFMLWindow> window ) :
   _renderData( renderData ),
   _window( window )
{
}

void PlayingStateRenderer::Render()
{
   _renderData->PlayerSprite->Tick();
   _renderData->NpcSprite->Tick();

   _window->Draw( _renderData->NpcSprite->GetSprite() );
   _window->Draw( _renderData->PlayerSprite->GetSprite() );
}
