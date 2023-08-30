#include <SFML/Graphics.hpp>

#include "PlayingStateRenderer.h"
#include "RenderConfig.h"
#include "SFMLWindow.h"
#include "RaycastRenderer.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

PlayingStateRenderer::PlayingStateRenderer( shared_ptr<RenderConfig> renderConfig,
                                            shared_ptr<SFMLWindow> window,
                                            shared_ptr<RaycastRenderer> raycastRenderer ) :
   _window( window ),
   _raycastRenderer( raycastRenderer )
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
   _raycastRenderer->Render();
   _window->Draw( _text );
}
