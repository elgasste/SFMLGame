#include "GameClock.h"
#include "RenderConfig.h"

using namespace NAMESPACE;
using namespace std;

GameClock::GameClock( shared_ptr<RenderConfig> renderConfig ) :
   _totalFrameCount( 0 ),
   _lagFrameCount( 0 ),
   _totalDuration( 0 ),
   _lastFrameSeconds( 0 )
{
   _minFrameDuration = chrono::nanoseconds( (long long)( ( 1 / (double)renderConfig->MaximumFrameRate ) * ONE_SECOND_NANO ) );
   _maxFrameDuration = chrono::nanoseconds( (long long)( ( 1 / (double)renderConfig->MinimumFrameRate ) * ONE_SECOND_NANO ) );

   _minFrameSeconds = _minFrameDuration;
   _maxFrameSeconds = _maxFrameDuration;

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
   _absoluteStartTime = chrono::steady_clock::now();
}

void GameClock::StartFrame()
{
   _frameStartTime = chrono::steady_clock::now();
}

void GameClock::EndFrame()
{
   static auto now = chrono::steady_clock::now();
   static auto lastFrameDuration = now - _frameStartTime;
   _totalFrameCount++;
   _totalDuration = now - _absoluteStartTime;

   if ( lastFrameDuration > _maxFrameDuration )
   {
      _lastFrameSeconds = _maxFrameSeconds;
      _lagFrameCount++;
   }
   else
   {
      static auto durationToSleep = _minFrameDuration - lastFrameDuration;

      if ( durationToSleep > chrono::nanoseconds( 0 ) )
      {
         _lastFrameSeconds = _minFrameSeconds;
         this_thread::sleep_for( durationToSleep );
      }
      else
      {
         _lastFrameSeconds = lastFrameDuration;
      }
   }
}

long long GameClock::GetAverageFrameRate() const
{
   // MUFFINS: figure this out later
   //return _totalFrameCount == 0 ? 0 : ( 1'000'000'000 / ( _totalDurationNano / _totalFrameCount ) );
   return 0ll;
}

long long GameClock::GetCurrentFrameRate() const
{
   return (long long)( 1 / GetFrameSeconds() );
}
