#include <SFML/Graphics.hpp>

#include "MenuStateRenderer.h"
#include "RenderConfig.h"
#include "SFMLWindow.h"
#include "GameClock.h"
#include "Menu.h"
#include "IMenuOption.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

MenuStateRenderer::MenuStateRenderer( shared_ptr<RenderConfig> renderConfig,
                                      shared_ptr<SFMLWindow> window,
                                      shared_ptr<GameClock> clock,
                                      shared_ptr<Menu> menu ) :
   _renderConfig( renderConfig ),
   _window( window ),
   _clock( clock ),
   _menu( menu ),
   _elapsedSeconds( 0 ),
   _showCarat( true )
{
   _font = make_shared<Font>();
   _font->loadFromFile( renderConfig->MenuFont );

   _text = make_shared<Text>();
   _text->setFont( *_font );
   _text->setCharacterSize( renderConfig->MenuCharSize );
   _text->setFillColor( renderConfig->MenuTextColor );

   _carat = make_shared<Text>();
   _carat->setFont( *_font );
   _carat->setCharacterSize( renderConfig->MenuCharSize );
   _carat->setFillColor( renderConfig->MenuTextColor );
   _carat->setString( ">" );

   _lineSpacing = _font->getLineSpacing( _text->getCharacterSize() );

   string menuText = "";

   for ( int i = 0; i < menu->GetOptionCount(); i++ )
   {
      if ( i > 0 )
      {
         menuText += "\n";
      }

      menuText += menu->GetOptionByIndex( i )->GetText();
   }

   _text->setString( menuText );

   auto textWidth = _text->getGlobalBounds().width;
   auto caratWidth = _carat->getGlobalBounds().width;
   auto menuWidth = textWidth + caratWidth + renderConfig->MenuCaratOffset;
   auto menuHeight = menu->GetOptionCount() * _lineSpacing;

   _menuX = ( (float)renderConfig->ScreenWidth / 2 ) - ( menuWidth / 2 );
   _menuY = ( (float)renderConfig->ScreenHeight / 2 ) - ( menuHeight / 2 );

   _text->setPosition( _menuX + caratWidth + renderConfig->MenuCaratOffset, _menuY );
}

void MenuStateRenderer::Render()
{
   _elapsedSeconds += _clock->GetFrameSeconds();

   if ( _elapsedSeconds >= _renderConfig->MenuCaratBlinkRate )
   {
      _elapsedSeconds = 0;
      _showCarat = !_showCarat;
   }

   _window->Draw( _text );

   if ( _showCarat )
   {
      _carat->setPosition( _menuX, _menuY + ( _menu->GetCurrentOptionIndex() * _lineSpacing ) );
      _window->Draw( _carat );
   }
}
