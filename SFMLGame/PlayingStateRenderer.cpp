#include <SFML/Graphics.hpp>

#include "PlayingStateRenderer.h"
#include "GameConfig.h"
#include "RenderConfig.h"
#include "SFMLWindow.h"
#include "BspRunner.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

PlayingStateRenderer::PlayingStateRenderer( shared_ptr<GameConfig> gameConfig,
                                            shared_ptr<RenderConfig> renderConfig,
                                            shared_ptr<SFMLWindow> window,
                                            shared_ptr<BspRunner> bspRunner ) :
   _window( window ),
   _bspRunner( bspRunner )
{
   _font = make_shared<Font>();
   _font->loadFromFile( renderConfig->MessageFont );

   _text = make_shared<Text>();
   _text->setFont( *_font );
   _text->setCharacterSize( renderConfig->MessageCharSize );
   _text->setFillColor( renderConfig->MessageTextColor );
   _text->setString( "Press ESC for menu, or F12 to toggle diagnostics" );

   _text->setPosition( ( (float)gameConfig->ScreenWidth / 2 ) - ( _text->getGlobalBounds().width / 2 ),
                       ( (float)gameConfig->ScreenHeight / 2 ) - ( _text->getGlobalBounds().height / 2 ) );
}

void PlayingStateRenderer::Render()
{
   _bspRunner->Run();
   _window->Draw( _text );
}
