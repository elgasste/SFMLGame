#include <format>
#include <chrono>

#include "DiagnosticsRenderer.h"
#include "RenderConfig.h"
#include "GameData.h"
#include "GameClock.h"
#include "SFMLWindow.h"
#include "Entity.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

DiagnosticsRenderer::DiagnosticsRenderer( shared_ptr<RenderConfig> renderConfig,
                                          shared_ptr<GameData> gameData,
                                          shared_ptr<GameClock> clock,
                                          shared_ptr<SFMLWindow> window ) :
   _renderConfig( renderConfig ),
   _gameData( gameData ),
   _clock( clock ),
   _window( window ),
   _currentFrameRateCache( 0 ),
   _elapsedSeconds( 0 )
{
   _font = make_shared<Font>();
   _font->loadFromFile( renderConfig->DiagnosticsFont );

   _text = make_shared<Text>();
   _text->setFont( *_font );
   _text->setCharacterSize( renderConfig->DiagnosticsCharSize );
   _text->setFillColor( renderConfig->DiagnosticsTextColor );

   _text->setPosition( renderConfig->DiagnosticsXPosition + renderConfig->DiagnosticsTextMargin,
                       renderConfig->DiagnosticsYPosition + renderConfig->DiagnosticsTextMargin );

   _background = shared_ptr<RectangleShape>( new RectangleShape( { renderConfig->DiagnosticsWidth, renderConfig->DiagnosticsHeight } ) );
   _background->setFillColor( renderConfig->DiagnosticsBackgroundColor );
   _background->setPosition( renderConfig->DiagnosticsXPosition, renderConfig->DiagnosticsYPosition );
}

void DiagnosticsRenderer::Render()
{
   _elapsedSeconds += _clock->GetFrameSeconds();

   if ( _elapsedSeconds >= _renderConfig->DiagnosticsCurrentFrameRateRefreshSeconds )
   {
      _currentFrameRateCache = _clock->GetCurrentFrameRate();
      _elapsedSeconds = 0;
   }

   static string text;
   text = "";

   text += format( IDS_MinimumFrameRate, _renderConfig->MinimumFrameRate ) + "\n";
   text += format( IDS_MaximumFrameRate, _renderConfig->MaximumFrameRate ) + "\n";
   text += format( IDS_CurrentFrameRate, _currentFrameRateCache ) + "\n";
   text += format( IDS_AverageFrameRate, _clock->GetAverageFrameRate() ) + "\n";
   text += format( IDS_TotalFrames, _clock->GetTotalFrameCount() ) + "\n";
   text += format( IDS_LagFrames, _clock->GetLagFrameCount() ) + "\n";
   text += format( IDS_TotalElapsedTime, chrono::round<chrono::seconds>( chrono::duration<float>{ _clock->GetTotalElapsedSeconds() } ) ) + "\n\n";

   auto ball = _gameData->GetBall();
   text += format( IDS_BallAngle, ball->GetAngle() ) + "\n";
   text += format( IDS_BallVelocity, ball->GetVelocity() );

   _text->setString( text );

   _window->Draw( _background );
   _window->Draw( _text );
}
