#include "MainMenuStateRenderer.h"
#include "GameConfig.h"
#include "GameData.h"
#include "RenderConfig.h"
#include "RenderData.h"
#include "SFMLWindow.h"
#include "GameClock.h"
#include "MainMenu.h"
#include "Entity.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

MainMenuStateRenderer::MainMenuStateRenderer( shared_ptr<GameConfig> gameConfig,
                                              shared_ptr<GameData> gameData,
                                              shared_ptr<RenderConfig> renderConfig,
                                              shared_ptr<RenderData> renderData,
                                              shared_ptr<SFMLWindow> window,
                                              shared_ptr<GameClock> clock,
                                              shared_ptr<MainMenu> menu ) :
   _gameData( gameData ),
   _renderConfig( renderConfig ),
   _window( window ),
   _clock( clock ),
   _menu( menu ),
   _currentOptionIndexCache( 0 ),
   _elapsedSeconds( 0 ),
   _showCarat( true )
{
   _backgroundRect = RectangleShape( { (float)renderConfig->ScreenWidth, (float)renderConfig->ScreenHeight } );
   _backgroundRect.setFillColor( renderConfig->MainMenuBackgroundColor );

   _font = make_shared<Font>();
   _font->loadFromFile( renderConfig->MainMenuFont );

   _text = make_shared<Text>();
   _text->setFont( *_font );
   _text->setCharacterSize( renderConfig->MainMenuCharSize );
   _text->setFillColor( renderConfig->MainMenuTextColor );

   _carat = make_shared<Text>();
   _carat->setFont( *_font );
   _carat->setCharacterSize( renderConfig->MainMenuCharSize );
   _carat->setFillColor( renderConfig->MainMenuTextColor );
   _carat->setString( ">" );

   _lineSpacing = _font->getLineSpacing( _text->getCharacterSize() );

   string menuText = "";

   for ( int i = 0; i < menu->GetOptionCount(); i++ )
   {
      if ( i > 0 )
      {
         menuText += "\n";
      }

      menuText += menu->GetOptionByIndex( i ).menuText;
   }

   _text->setString( menuText );

   auto textWidth = _text->getGlobalBounds().width;
   auto caratWidth = _carat->getGlobalBounds().width;
   auto menuWidth = textWidth + caratWidth + renderConfig->MainMenuCaratOffset;
   auto menuHeight = menu->GetOptionCount() * _lineSpacing;

   _menuX = ( (float)renderConfig->ScreenWidth / 2 ) - ( menuWidth / 2 );
   _menuY = ( (float)renderConfig->ScreenHeight / 2 ) - ( menuHeight / 2 );

   _text->setPosition( _menuX + caratWidth + renderConfig->MainMenuCaratOffset, _menuY );

   _ballSprite = Sprite( *( renderData->GetBallTexture() ) );
   _ballSprite.setOrigin( renderConfig->BallOrigin );
   auto scalar = gameConfig->BallDiameter / renderData->GetBallTexture()->getSize().x;
   _ballSprite.setScale( scalar, scalar );
   _ballSprite.setColor( renderConfig->MainMenuBallDimmer );
}

void MainMenuStateRenderer::Render()
{
   _window->Draw( _backgroundRect );

   _ballSprite.setPosition( _gameData->GetBall()->GetPosition() );
   _window->Draw( _ballSprite );

   if ( _menu->GetCurrentOptionIndex() != _currentOptionIndexCache )
   {
      _currentOptionIndexCache = _menu->GetCurrentOptionIndex();
      _showCarat = true;
      _elapsedSeconds = 0;
   }
   else
   {
      _elapsedSeconds += _clock->GetFrameSeconds();
   }

   if ( _elapsedSeconds >= _renderConfig->MainMenuCaratBlinkRate )
   {
      _elapsedSeconds = 0;
      _showCarat = !_showCarat;
   }

   _window->Draw( _text );

   if ( _showCarat )
   {
      _carat->setPosition( _menuX, _menuY + ( _currentOptionIndexCache * _lineSpacing ) );
      _window->Draw( _carat );
   }
}
