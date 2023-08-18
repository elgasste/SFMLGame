#include "PlayingStateRenderer.h"
#include "RenderConfig.h"
#include "RenderData.h"
#include "GameConfig.h"
#include "GameData.h"
#include "SFMLWindow.h"
#include "Entity.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

PlayingStateRenderer::PlayingStateRenderer( shared_ptr<RenderConfig> renderConfig,
                                            shared_ptr<RenderData> renderData,
                                            shared_ptr<GameConfig> gameConfig,
                                            shared_ptr<GameData> gameData,
                                            shared_ptr<SFMLWindow> window ) :
   _gameData( gameData ),
   _window( window )
{
   _backgroundRect = RectangleShape( { (float)renderConfig->ScreenWidth, (float)renderConfig->ScreenHeight } );
   _backgroundRect.setFillColor( renderConfig->ArenaBackgroundColor );

   _font = make_shared<Font>();
   _font->loadFromFile( renderConfig->MessageFont );

   _text = make_shared<Text>();
   _text->setFont( *_font );
   _text->setCharacterSize( renderConfig->MessageCharSize );
   _text->setFillColor( renderConfig->MessageTextColor );
   _text->setString( IDS_PlayStateMessage );

   _text->setPosition( ( (float)renderConfig->ScreenWidth / 2 ) - ( _text->getGlobalBounds().width / 2 ),
                       ( (float)renderConfig->ScreenHeight / 2 ) - ( _text->getGlobalBounds().height / 2 ) );

   _ballSprite = Sprite( *( renderData->GetBallTexture() ) );
   _ballSprite.setOrigin( renderConfig->BallOrigin );
   auto scalar = gameConfig->BallDiameter / renderData->GetBallTexture()->getSize().x;
   _ballSprite.setScale( scalar, scalar );
}

void PlayingStateRenderer::Render()
{
   _window->Draw( _backgroundRect );

   _ballSprite.setPosition( _gameData->GetBall()->GetPosition() );
   _window->Draw( _ballSprite );

   _window->Draw( _text );
}
