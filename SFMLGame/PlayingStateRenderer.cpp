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
   _font->loadFromFile( renderConfig->PlayingMessageFont );

   _text = make_shared<Text>();
   _text->setFont( *_font );
   _text->setCharacterSize( renderConfig->PlayingMessageCharSize );
   _text->setFillColor( renderConfig->PlayingMessageTextColor );
   _text->setString( IDS_PlayStateMessage );

   _text->setPosition( ( (float)renderConfig->ScreenWidth / 2 ) - ( _text->getGlobalBounds().width / 2 ),
                       ( (float)renderConfig->ScreenHeight / 2 ) - ( _text->getGlobalBounds().height / 2 ) );

   _playerSprite = Sprite( *( renderData->GetPlayerSpriteTexture() ) );
   _playerSprite.setTextureRect( { 0, 0, renderConfig->PlayerSpriteSize.x, renderConfig->PlayerSpriteSize.y } );
   _playerSprite.setScale( renderConfig->SpriteScalar, renderConfig->SpriteScalar );
   _playerSprite.setOrigin( renderConfig->PlayerSpriteOrigin );
}

void PlayingStateRenderer::Render()
{
   _window->Draw( _backgroundRect );

   _playerSprite.setPosition( _gameData->GetPlayer()->GetPosition() );
   _window->Draw( _playerSprite );

   _window->Draw( _text );
}
