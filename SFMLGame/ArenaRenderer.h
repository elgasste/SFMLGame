#pragma once

#include "Common.h"

namespace sf
{
   class RectangleShape;
}

NAMESPACE_BEGIN

class GameConfig;
class SFMLWindow;
class Arena;

class ArenaRenderer
{
public:
   ArenaRenderer( std::shared_ptr<GameConfig> config,
                  std::shared_ptr<SFMLWindow> window,
                  std::shared_ptr<Arena> arena );

   void Render();

private:
   std::shared_ptr<SFMLWindow> _window;
   std::shared_ptr<Arena> _arena;

   std::shared_ptr<sf::RectangleShape> _playerRect;
};

NAMESPACE_END
