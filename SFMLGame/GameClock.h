#pragma once

#include "Common.h"

namespace sf
{
   class Clock;
   class Time;
}

NAMESPACE_BEGIN

class RenderConfig;

class GameClock
{
public:
   GameClock( std::shared_ptr<RenderConfig> renderConfig );

   void Initialize();
   void StartFrame();
   void EndFrame();

   unsigned int GetTotalFrameCount() const { return _totalFrameCount; }
   unsigned int GetLagFrameCount() const { return _lagFrameCount; }
   unsigned int GetAverageFrameRate() const;
   unsigned int GetCurrentFrameRate() const;

   float GetFrameSeconds() const { return _lastFrameSeconds; }

private:
   sf::Clock _clock;

   sf::Time _minFrameDuration;
   sf::Time _maxFrameDuration;

   unsigned int _totalFrameCount;
   unsigned int _lagFrameCount;

   sf::Time _absoluteStartTime;
   sf::Time _frameStartTime;
   sf::Time _totalDuration;

   float _lastFrameSeconds;
};

NAMESPACE_END
