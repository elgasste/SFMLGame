#include <format>

#include <SFML/Graphics.hpp>

#include "DiagnosticsRenderer.h"
#include "RenderConfig.h"
#include "GameClock.h"
#include "SFMLWindow.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

DiagnosticsRenderer::DiagnosticsRenderer( shared_ptr<RenderConfig> renderConfig,
                                          shared_ptr<GameClock> clock,
                                          shared_ptr<SFMLWindow> window ) :
   _renderConfig( renderConfig ),
   _clock( clock ),
   _window( window )
{
   _font = make_shared<Font>();
   _font->loadFromFile( renderConfig->DiagnosticsFont );

   _text = make_shared<Text>();
   _text->setFont( *_font );
   _text->setCharacterSize( renderConfig->DiagnosticsCharSize );
   _text->setFillColor( renderConfig->DiagnosticsTextColor );

   _text->setPosition( renderConfig->DiagnosticsXPosition + renderConfig->DiagnosticsTextMargin,
                       renderConfig->DiagnosticsYPosition + renderConfig->DiagnosticsTextMargin );

   _background = shared_ptr<sf::RectangleShape>( new RectangleShape( { renderConfig->DiagnosticsWidth, renderConfig->DiagnosticsHeight } ) );
   _background->setFillColor( renderConfig->DiagnosticsBackgroundColor );
   _background->setPosition( renderConfig->DiagnosticsXPosition, renderConfig->DiagnosticsYPosition );
}

void DiagnosticsRenderer::Render()
{
   string text;

   text += format( "Maximum Frame Rate: {}", _renderConfig->MaximumFrameRate );
   text += format( "\nCurrent Frame Rate: {}", _clock->GetCurrentFrameRate() );
   text += format( "\nAverage Frame Rate: {}", _clock->GetAverageFrameRate() );
   text += format( "\nTotal Frames:       {}", _clock->GetTotalFrameCount() );
   text += format( "\nLag Frames:         {}", _clock->GetLagFrameCount() );

   _text->setString( text );

   _window->Draw( _background );
   _window->Draw( _text );
}
