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
   _backgroundRect = RectangleShape( { (float)renderConfig->ScreenWidth, (float)renderConfig->ScreenHeight } );
   _backgroundRect.setFillColor( renderConfig->ArenaBackgroundColor );
}

void PlayingStateRenderer::Render()
{
   _window->Draw( _backgroundRect );

   // MUFFINS: should the new positioning happen elsewhere? or is this the place to put it?
   auto playerSprite = _renderData->GetPlayerSprite();
   playerSprite->SetPosition( _gameData->GetPlayer()->GetPosition() );

   _window->Draw( playerSprite->GetSprite() );
}
