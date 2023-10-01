#include "WindowsLibs.h"
#include <timeapi.h>
#include <chrono>
#include <thread>

#include "GameClock.h"
#include "RenderConfig.h"

using namespace NAMESPACE;
using namespace std;

GameClock::GameClock( shared_ptr<RenderConfig> renderConfig ) :
   _totalFrameCount( 0 ),
   _lagFrameCount( 0 ),
   _absoluteStartTimeNano( 0 ),
   _frameStartTimeNano( 0 ),
   _totalDurationNano( 0 ),
   _lastFrameSeconds( 0 )
{
   _minNanoSecondsPerFrame = (long long)( ( 1 / (double)renderConfig->MaximumFrameRate ) * 1'000'000'000 );
   _maxNanoSecondsPerFrame = (long long)( ( 1 / (double)renderConfig->MinimumFrameRate ) * 1'000'000'000 );

   _minFrameSeconds = _minNanoSecondsPerFrame / 1'000'000'000.0f;
   _maxFrameSeconds = _maxNanoSecondsPerFrame / 1'000'000'000.0f;

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
   _absoluteStartTimeNano = chrono::steady_clock::now().time_since_epoch().count();
}

void GameClock::StartFrame()
{
   _frameStartTimeNano = chrono::steady_clock::now().time_since_epoch().count();
}

void GameClock::EndFrame()
{
   static auto now = chrono::steady_clock::now().time_since_epoch().count();
   static auto lastFrameDurationNano = now - _frameStartTimeNano;
   _totalFrameCount++;
   _totalDurationNano = now - _absoluteStartTimeNano;

   if ( lastFrameDurationNano > _maxNanoSecondsPerFrame )
   {
      _lastFrameSeconds = _maxFrameSeconds;
      _lagFrameCount++;
   }
   else
   {
      static auto nanoSecondsToSleep = _minNanoSecondsPerFrame - lastFrameDurationNano;

      if ( nanoSecondsToSleep > 0 )
      {
         _lastFrameSeconds = _minFrameSeconds;
         this_thread::sleep_for( chrono::nanoseconds( nanoSecondsToSleep ) );
      }
      else
      {
         _lastFrameSeconds = lastFrameDurationNano / 1'000'000'000.0f;
      }
   }
}

// TODO: it still seems like something is wrong with this calculation, not sure why I feel that way
long long GameClock::GetAverageFrameRate() const
{
   return _totalFrameCount == 0 ? 0 : ( 1'000'000'000 / ( _totalDurationNano / _totalFrameCount ) );
}

long long GameClock::GetCurrentFrameRate() const
{
   return (long long)( 1 / GetFrameSeconds() );
}
