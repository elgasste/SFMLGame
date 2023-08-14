#pragma once

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Common.h"

namespace sf
{
   class RenderWindow;
   class Drawable;
   class Vertex;
}

NAMESPACE_BEGIN

class GameConfig;
class EventAggregator;
class GameClock;

class SFMLWindow
{
public:
   SFMLWindow( std::shared_ptr<GameConfig> gameConfig,
               std::shared_ptr<EventAggregator> eventAggregator,
               std::shared_ptr<GameClock> clock );

   void Initialize();
   void Show() const;
   void HandleEvents() const;
   void Clear() const;
   void Draw( std::shared_ptr<sf::Drawable> drawable ) const;
   void Draw( const sf::Drawable& drawable ) const;
   void Draw( const sf::Vertex* vertices, size_t vertexCount, sf::PrimitiveType type ) const;
   void Render() const;

private:
   std::shared_ptr<GameConfig> _gameConfig;
   std::shared_ptr<EventAggregator> _eventAggregator;
   std::shared_ptr<GameClock> _clock;

   std::shared_ptr<sf::RenderWindow> _window;
};

NAMESPACE_END
