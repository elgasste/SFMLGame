#include "GameClock.h"
#include "RenderConfig.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

GameClock::GameClock( shared_ptr<RenderConfig> renderConfig ) :
   _totalFrameCount( 0 ),
   _lagFrameCount( 0 ),
   _lastFrameSeconds( 0 ),
   _totalElapsedSeconds( 0 )
{
   _minFrameDuration = seconds( 1 / (float)renderConfig->MaximumFrameRate );
   _maxFrameDuration = seconds( 1 / (float)renderConfig->MinimumFrameRate );
}

void GameClock::StartFrame()
{
   _frameStartTime = _clock.getElapsedTime();
}

void GameClock::EndFrame()
{
   _totalFrameCount++;
   auto lastFrameDuration = _clock.getElapsedTime() - _frameStartTime;

   if ( lastFrameDuration > _maxFrameDuration )
   {
      _lastFrameSeconds = _maxFrameDuration.asSeconds();
      _totalElapsedSeconds += _lastFrameSeconds;
      _lagFrameCount++;
      return;
   }
   else if ( lastFrameDuration < _minFrameDuration )
   {
      // any "sleep" call is notoriously unreliable, so we'll try to do it, but we'll
      // still use the actual elapsed time below to record the last frame's seconds.
      sleep( _minFrameDuration - lastFrameDuration );
   }

   _lastFrameSeconds = ( _clock.getElapsedTime() - _frameStartTime ).asSeconds();
   _totalElapsedSeconds += _lastFrameSeconds;
}

unsigned int GameClock::GetAverageFrameRate() const
{
   return _totalFrameCount == 0 ? 0 : (unsigned int)( 1 / ( _totalElapsedSeconds / _totalFrameCount ) );
}

unsigned int GameClock::GetCurrentFrameRate() const
{
   return (unsigned int)( 1 / GetFrameSeconds() );
}
