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

   long long GetTotalFrameCount() const { return _totalFrameCount; }
   long long GetLagFrameCount() const { return _lagFrameCount; }
   long long GetAverageFrameRate() const;
   long long GetCurrentFrameRate() const;

   float GetFrameSeconds() const { return _lastFrameSeconds; }

private:
   std::chrono::nanoseconds _minFrameDuration;
   std::chrono::nanoseconds _maxFrameDuration;

   long long _totalFrameCount;
   long long _lagFrameCount;

   std::chrono::steady_clock::time_point _absoluteStartTime;
   std::chrono::steady_clock::time_point _frameStartTime;
   std::chrono::nanoseconds _totalDuration;

   float _lastFrameSeconds;
};

NAMESPACE_END
