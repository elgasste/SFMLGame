#include <SFML/Graphics.hpp>

#include "LoadingStateRenderer.h"
#include "GameConfig.h"
#include "SFMLWindow.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

LoadingStateRenderer::LoadingStateRenderer( shared_ptr<GameConfig> config,
                                            shared_ptr<SFMLWindow> window ) :
   _window( window )
{
   _font = make_shared<Font>();
   _font->loadFromFile( config->LoadingTextFont );

   _text = make_shared<Text>();
   _text->setFont( *_font );
   _text->setCharacterSize( config->LoadingCharSize );
   _text->setFillColor( config->LoadingTextColor );
   _text->setString( "We're loading, hold your horses..." );

   _text->setPosition( config->LoadingTextMargin, config->LoadingTextMargin );
}

void LoadingStateRenderer::Render()
{
   _window->Draw( _text );
}
