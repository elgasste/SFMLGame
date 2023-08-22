#include "TitleScreenStateRenderer.h"
#include "RenderConfig.h"
#include "SFMLWindow.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

TitleScreenStateRenderer::TitleScreenStateRenderer( shared_ptr<RenderConfig> renderConfig,
                                                    shared_ptr<SFMLWindow> window ) :
   _window( window )
{
   _font = make_shared<Font>();
   _font->loadFromFile( renderConfig->TitleMessageFont );

   _text = make_shared<Text>();
   _text->setString( IDS_TitleStateMessage );
   _text->setFont( *_font );
   _text->setCharacterSize( renderConfig->TitleMessageCharSize );
   _text->setFillColor( renderConfig->TitleMessageTextColor );

   auto lineSpacing = _font->getLineSpacing( _text->getCharacterSize() );

   auto messageX = ( (float)renderConfig->ScreenWidth / 2 ) - ( _text->getGlobalBounds().width / 2 );
   auto messageY = ( (float)renderConfig->ScreenHeight / 2 ) - ( lineSpacing / 2 );

   _text->setPosition( messageX + renderConfig->MainMenuCaratOffset, messageY );
}

void TitleScreenStateRenderer::Render()
{
   _window->Draw( _text );
}
