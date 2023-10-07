#include "GameClock.h"
#include "RenderConfig.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

GameClock::GameClock( shared_ptr<RenderConfig> renderConfig ) :
   _totalFrameCount( 0 ),
   _lagFrameCount( 0 ),
   _lastFrameSeconds( 0 )
{
   _minFrameDuration = milliseconds( (Int32)( ( 1 / (double)renderConfig->MaximumFrameRate ) * 1000 ) );
   _maxFrameDuration = milliseconds( (Int32)( ( 1 / (double)renderConfig->MinimumFrameRate ) * 1000 ) );
}

void GameClock::Initialize()
{
   _absoluteStartTime = _clock.restart();
}

void GameClock::StartFrame()
{
   _frameStartTime = _clock.getElapsedTime();
}

void GameClock::EndFrame()
{
   _totalFrameCount++;
   auto now = _clock.getElapsedTime();
   auto lastFrameDuration = now - _frameStartTime;
   _totalDuration = now - _absoluteStartTime;

   if ( lastFrameDuration > _maxFrameDuration )
   {
      lastFrameDuration = _maxFrameDuration;
      _lagFrameCount++;
   }
   else if ( lastFrameDuration <= _minFrameDuration )
   {
      auto durationToSleep = _minFrameDuration - lastFrameDuration;
      lastFrameDuration = _minFrameDuration;
      _totalDuration += durationToSleep;
      sleep( durationToSleep );
   }

   _lastFrameSeconds = lastFrameDuration.asSeconds();
}

unsigned int GameClock::GetAverageFrameRate() const
{
   return _totalFrameCount == 0 ? 0 : (unsigned int)( _totalDuration.asSeconds() / _totalFrameCount );
}

unsigned int GameClock::GetCurrentFrameRate() const
{
   return (unsigned int)( 1 / GetFrameSeconds() );
}
