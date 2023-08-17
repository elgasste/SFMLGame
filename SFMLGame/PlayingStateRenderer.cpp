#include "PlayingStateRenderer.h"
#include "RenderConfig.h"
#include "SFMLWindow.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

PlayingStateRenderer::PlayingStateRenderer( shared_ptr<RenderConfig> renderConfig,
                                            shared_ptr<RenderData> renderData,
                                            shared_ptr<SFMLWindow> window ) :
   _window( window )
{
   _font = make_shared<Font>();
   _font->loadFromFile( renderConfig->MessageFont );

   _text = make_shared<Text>();
   _text->setFont( *_font );
   _text->setCharacterSize( renderConfig->MessageCharSize );
   _text->setFillColor( renderConfig->MessageTextColor );
   _text->setString( IDS_PlayStateMessage );

   _text->setPosition( ( (float)renderConfig->ScreenWidth / 2 ) - ( _text->getGlobalBounds().width / 2 ),
                       ( (float)renderConfig->ScreenHeight / 2 ) - ( _text->getGlobalBounds().height / 2 ) );
}

void PlayingStateRenderer::Render()
{
   _window->Draw( _text );
}
