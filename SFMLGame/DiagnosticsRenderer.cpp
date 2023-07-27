#include <format>

#include <SFML/Graphics.hpp>

#include "DiagnosticsRenderer.h"
#include "GameConfig.h"
#include "GameClock.h"
#include "SFMLWindow.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

DiagnosticsRenderer::DiagnosticsRenderer( shared_ptr<GameConfig> gameConfig,
                                          shared_ptr<GameClock> clock,
                                          shared_ptr<SFMLWindow> window ) :
   _gameConfig( gameConfig ),
   _clock( clock ),
   _window( window )
{
   _font = make_shared<Font>();
   _font->loadFromFile( gameConfig->DiagnosticsFont );

   _text = make_shared<Text>();
   _text->setFont( *_font );
   _text->setCharacterSize( gameConfig->DiagnosticsCharSize );
   _text->setFillColor( gameConfig->DiagnosticsTextColor );

   _text->setPosition( gameConfig->DiagnosticsXPosition + gameConfig->DiagnosticsTextMargin,
                       gameConfig->DiagnosticsYPosition + gameConfig->DiagnosticsTextMargin );

   _background = shared_ptr<sf::RectangleShape>( new RectangleShape( { gameConfig->DiagnosticsWidth, gameConfig->DiagnosticsHeight } ) );
   _background->setFillColor( gameConfig->DiagnosticsBackgroundColor );
   _background->setPosition( gameConfig->DiagnosticsXPosition, gameConfig->DiagnosticsYPosition );
}

void DiagnosticsRenderer::Render()
{
   string text;

   text += format( "Maximum Frame Rate: {}", _gameConfig->MaximumFrameRate );
   text += format( "\nCurrent Frame Rate: {}", _clock->GetCurrentFrameRate() );
   text += format( "\nAverage Frame Rate: {}", _clock->GetAverageFrameRate() );
   text += format( "\nTotal Frames:       {}", _clock->GetTotalFrameCount() );
   text += format( "\nLag Frames:         {}", _clock->GetLagFrameCount() );

   _text->setString( text );

   _window->Draw( _background );
   _window->Draw( _text );
}
