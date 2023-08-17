#pragma once

#include "Common.h"

namespace sf
{
   class RenderWindow;
   class Drawable;
}

NAMESPACE_BEGIN

class RenderConfig;
class EventAggregator;
class GameClock;

class SFMLWindow
{
public:
   SFMLWindow( std::shared_ptr<RenderConfig> renderConfig,
               std::shared_ptr<EventAggregator> eventAggregator,
               std::shared_ptr<GameClock> clock );

   void Initialize();
   void Show() const;
   void HandleEvents() const;
   void Clear() const;
   void Draw( std::shared_ptr<sf::Drawable> drawable ) const;
   void Draw( const sf::Drawable& drawable ) const;
   void Render() const;

private:
   std::shared_ptr<RenderConfig> _renderConfig;
   std::shared_ptr<EventAggregator> _eventAggregator;
   std::shared_ptr<GameClock> _clock;

   std::shared_ptr<sf::RenderWindow> _window;
};

NAMESPACE_END
