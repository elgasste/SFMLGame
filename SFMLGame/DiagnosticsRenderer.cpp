#include <format>

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

   _background = shared_ptr<RectangleShape>( new RectangleShape( { renderConfig->DiagnosticsWidth, renderConfig->DiagnosticsHeight } ) );
   _background->setFillColor( renderConfig->DiagnosticsBackgroundColor );
   _background->setPosition( renderConfig->DiagnosticsXPosition, renderConfig->DiagnosticsYPosition );
}

void DiagnosticsRenderer::Render()
{
   static string text;
   text = "";

   text += format( IDS_MaximumFrameRate, _renderConfig->MaximumFrameRate ) + "\n";
   text += format( IDS_CurrentFrameRate, _clock->GetCurrentFrameRate() ) + "\n";
   text += format( IDS_AverageFrameRate, _clock->GetAverageFrameRate() ) + "\n";
   text += format( IDS_TotalFrames, _clock->GetTotalFrameCount() ) + "\n";
   text += format( IDS_LagFrames, _clock->GetLagFrameCount() ) + "\n\n";

   auto ball = _gameData->GetBall();
   text += format( IDS_BallAngle, ball->GetAngle() ) + "\n";
   text += format( IDS_BallVelocity, ball->GetVelocity() );

   _text->setString( text );

   _window->Draw( _background );
   _window->Draw( _text );
}
