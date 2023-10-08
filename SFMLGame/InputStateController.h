#pragma once

#include "Common.h"
#include "Button.h"
#include "ButtonState.h"

NAMESPACE_BEGIN

class GameConfig;
class RenderConfig;

class InputStateController
{
public:
   InputStateController( std::shared_ptr<GameConfig> gameConfig );

   void KeyPressed( sf::Keyboard::Key key );
   void KeyReleased( sf::Keyboard::Key key );
   void UpdateKeyStates();
   void ReadMouseInput();

   bool WasButtonPressed( Button button ) const;
   bool IsButtonDown( Button button ) const;
   bool WasAnyButtonPressed() const;
   const sf::Vector2i& GetMousePosition() const { return _mousePosition; }
   const sf::Vector2i& GetMousePreviousPosition() const { return _mousePreviousPosition; }
   const sf::Vector2i& GetMouseDelta() const { return _mouseDelta; }

private:
   std::shared_ptr<GameConfig> _gameConfig;

   std::map<Button, ButtonState> _buttonStates;

   sf::Vector2i _mousePosition;
   sf::Vector2i _mousePreviousPosition;
   sf::Vector2i _mouseDelta;
};

NAMESPACE_END
