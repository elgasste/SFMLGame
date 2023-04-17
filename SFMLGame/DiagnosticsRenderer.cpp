#include <format>

#include <SFML/Graphics.hpp>

#include "DiagnosticsRenderer.h"
#include "GameConfig.h"
#include "GameClock.h"
#include "SFMLWindow.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

DiagnosticsRenderer::DiagnosticsRenderer( shared_ptr<GameConfig> config,
                                          shared_ptr<GameClock> clock,
                                          shared_ptr<SFMLWindow> window ) :
   _config( config ),
   _clock( clock ),
   _window( window )
{
   _font = make_shared<Font>();
   _font->loadFromFile( config->DiagnosticsFont );

   _text = make_shared<Text>();
   _text->setFont( *_font );
   _text->setCharacterSize( config->DiagnosticsCharSize );
   _text->setFillColor( config->DiagnosticsTextColor );

   _text->setPosition( config->DiagnosticsXPosition + config->DiagnosticsTextMargin,
                       config->DiagnosticsYPosition + config->DiagnosticsTextMargin );

   _background = shared_ptr<sf::RectangleShape>( new RectangleShape( { config->DiagnosticsWidth, config->DiagnosticsHeight } ) );
   _background->setFillColor( config->DiagnosticsBackgroundColor );
   _background->setPosition( config->DiagnosticsXPosition, config->DiagnosticsYPosition );
}

void DiagnosticsRenderer::Render()
{
   string text;

   text += format( "Maximum Frame Rate: {}", _config->MaximumFrameRate );
   text += format( "\nCurrent Frame Rate: {}", _clock->GetCurrentFrameRate() );
   text += format( "\nAverage Frame Rate: {}", _clock->GetAverageFrameRate() );
   text += format( "\nTotal Frames:       {}", _clock->GetTotalFrameCount() );
   text += format( "\nLag Frames:         {}", _clock->GetLagFrameCount() );

   _text->setString( text );

   _window->Draw( _background );
   _window->Draw( _text );
}
