#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class RenderConfig;

class GameClock
{
public:
   GameClock( std::shared_ptr<RenderConfig> renderConfig );
   ~GameClock();

   void Initialize();
   void StartFrame();
   void EndFrame();

   float GetFrameSeconds() const { return _lastFrameSeconds; }
   long long GetTotalFrameCount() const { return _totalFrameCount; }
   long long GetLagFrameCount() const { return _lagFrameCount; }
   long long GetElapsedNanoseconds() const { return _totalDurationNano; }
   long long GetAverageFrameRate() const;
   long long GetCurrentFrameRate() const;

private:
   long long _minNanoSecondsPerFrame;
   long long _maxNanoSecondsPerFrame;

   float _minFrameSeconds;
   float _maxFrameSeconds;

   long long _totalFrameCount;
   long long _lagFrameCount;
   long long _absoluteStartTimeNano;
   long long _frameStartTimeNano;
   long long _totalDurationNano;
   float _lastFrameSeconds;
};

NAMESPACE_END
