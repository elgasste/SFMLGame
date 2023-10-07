#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class RenderConfig;
class GameClock;
class InputStateController;

class SFMLWindow
{
public:
   SFMLWindow( std::shared_ptr<RenderConfig> renderConfig,
               std::shared_ptr<GameClock> clock,
               std::shared_ptr<InputStateController> inputStateController );

   void Initialize();
   void Show() const;
   void HandleEvents() const;
   void Clear() const;
   void Draw( std::shared_ptr<sf::Drawable> drawable ) const;
   void Draw( const sf::Drawable& drawable ) const;
   void Render() const;

private:
   std::shared_ptr<RenderConfig> _renderConfig;
   std::shared_ptr<GameClock> _clock;
   std::shared_ptr<InputStateController> _inputStateController;

   std::shared_ptr<sf::RenderWindow> _window;
};

NAMESPACE_END
