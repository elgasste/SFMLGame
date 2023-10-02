#include "GameClock.h"
#include "RenderConfig.h"

using namespace NAMESPACE;
using namespace std;

GameClock::GameClock( shared_ptr<RenderConfig> renderConfig ) :
   _totalFrameCount( 0 ),
   _lagFrameCount( 0 ),
   _totalDuration( 0 ),
   _lastFrameDuration( 0 )
{
   _minFrameDuration = chrono::nanoseconds( (long long)( ( 1 / (double)renderConfig->MaximumFrameRate ) * 1'000'000'000 ) );
   _maxFrameDuration = chrono::nanoseconds( (long long)( ( 1 / (double)renderConfig->MinimumFrameRate ) * 1'000'000'000 ) );

   // According to documentation, this sets the system's minimum clock resolution to
   // 1 millisecond. Without it, higher frame rates have unpredictable results in Windows.
   timeBeginPeriod( 1 );
}

GameClock::~GameClock()
{
   timeEndPeriod( 1 );
}

void GameClock::Initialize()
{
   _absoluteStartTime = chrono::high_resolution_clock::now();
}

void GameClock::StartFrame()
{
   _frameStartTime = chrono::high_resolution_clock::now();
}

void GameClock::EndFrame()
{
   static auto now = chrono::high_resolution_clock::now();
   static auto lastFrameDuration = now - _frameStartTime;
   _totalFrameCount++;
   _totalDuration = now - _absoluteStartTime;

   if ( lastFrameDuration > _maxFrameDuration )
   {
      _lastFrameDuration = _maxFrameDuration;
      _lagFrameCount++;
   }
   else if ( lastFrameDuration < _minFrameDuration )
   {
      _lastFrameDuration = _minFrameDuration;
      static auto durationToSleep = _minFrameDuration - lastFrameDuration;
      this_thread::sleep_for( durationToSleep );
   }
   else
   {
      _lastFrameDuration = lastFrameDuration;
   }
}

long long GameClock::GetAverageFrameRate() const
{
   return _totalFrameCount == 0 ? 0 : ( _totalDuration / _totalFrameCount ).count();
}

long long GameClock::GetCurrentFrameRate() const
{
   return (long long)( 1 / GetFrameSeconds() );
}
