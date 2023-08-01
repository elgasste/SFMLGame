#include <SFML/Graphics.hpp>

#include "PlayingStateRenderer.h"
#include "GameConfig.h"
#include "RenderConfig.h"
#include "SFMLWindow.h"
#include "BspOperator.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

PlayingStateRenderer::PlayingStateRenderer( shared_ptr<GameConfig> gameConfig,
                                            shared_ptr<RenderConfig> renderConfig,
                                            shared_ptr<SFMLWindow> window,
                                            shared_ptr<BspOperator> bspOperator,
                                            shared_ptr<Entity> player ) :
   _window( window ),
   _bspOperator( bspOperator ),
   _player( player )
{
   _font = make_shared<Font>();
   _font->loadFromFile( renderConfig->MessageFont );

   _text = make_shared<Text>();
   _text->setFont( *_font );
   _text->setCharacterSize( renderConfig->MessageCharSize );
   _text->setFillColor( renderConfig->MessageTextColor );
   _text->setString( "Press ESC for menu, or F12 to toggle diagnostics" );

   _text->setPosition( 12, 0 );
}

void PlayingStateRenderer::Render()
{
   _bspOperator->RenderWorld( _player );
   _window->Draw( _text );
}
