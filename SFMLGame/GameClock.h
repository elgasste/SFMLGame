#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class RenderConfig;

class GameClock
{
public:
   GameClock( std::shared_ptr<RenderConfig> renderConfig );

   void StartFrame();
   void EndFrame();

   unsigned int GetTotalFrameCount() const { return _totalFrameCount; }
   unsigned int GetLagFrameCount() const { return _lagFrameCount; }
   unsigned int GetAverageFrameRate() const;
   unsigned int GetCurrentFrameRate() const;

   float GetFrameSeconds() const { return _lastFrameSeconds; }
   float GetTotalElapsedSeconds() const { return _totalElapsedSeconds; }

private:
   sf::Clock _clock;

   sf::Time _minFrameDuration;
   sf::Time _maxFrameDuration;

   unsigned int _totalFrameCount;
   unsigned int _lagFrameCount;

   sf::Time _frameStartTime;

   float _lastFrameSeconds;
   float _totalElapsedSeconds;
};

NAMESPACE_END
