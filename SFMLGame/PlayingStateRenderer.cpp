#include <SFML/Graphics.hpp>

#include "PlayingStateRenderer.h"
#include "GameConfig.h"
#include "SFMLWindow.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

PlayingStateRenderer::PlayingStateRenderer( shared_ptr<GameConfig> config,
                                            shared_ptr<SFMLWindow> window ) :
   _window( window )
{
   _font = make_shared<Font>();
   _font->loadFromFile( config->MessageFont );

   _text = make_shared<Text>();
   _text->setFont( *_font );
   _text->setCharacterSize( config->MessageCharSize );
   _text->setFillColor( config->MessageTextColor );
   _text->setString( "Press ESC for menu, or F12 to toggle diagnostics" );

   _text->setPosition( ( config->ScreenWidth / 2 ) - ( _text->getGlobalBounds().width / 2 ),
                       ( config->ScreenHeight / 2 ) - ( _text->getGlobalBounds().height / 2 ) );
}

void PlayingStateRenderer::Render()
{
   _window->Draw( _text );
}
