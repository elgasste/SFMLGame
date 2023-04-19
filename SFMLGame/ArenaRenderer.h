#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class RenderData;
class SFMLWindow;
class GameClock;
class Arena;

class ArenaRenderer
{
public:
   ArenaRenderer( std::shared_ptr<RenderData> renderData,
                  std::shared_ptr<SFMLWindow> window,
                  std::shared_ptr<GameClock> clock,
                  std::shared_ptr<Arena> arena );

   void Render();

private:
   std::shared_ptr<RenderData> _renderData;
   std::shared_ptr<SFMLWindow> _window;
   std::shared_ptr<GameClock> _clock;
   std::shared_ptr<Arena> _arena;

   int _playerSpriteFrame;
   float _elapsedMovementSeconds;
};

NAMESPACE_END
