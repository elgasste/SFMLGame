#pragma once

#include "Common.h"
#include "Button.h"
#include "ButtonState.h"
#include "KeyCode.h"

NAMESPACE_BEGIN

class GameConfig;
class RenderConfig;

class InputReader
{
public:
   InputReader( std::shared_ptr<GameConfig> gameConfig );

   void ReadInput();
   bool WasButtonPressed( Button button ) const;
   bool IsButtonDown( Button button ) const;
   bool WasAnyButtonPressed() const;
   const sf::Vector2i& GetMousePosition() const { return _mousePosition; }
   const sf::Vector2i& GetMousePreviousPosition() const { return _mousePreviousPosition; }
   const sf::Vector2i& GetMouseDelta() const { return _mouseDelta; }

private:
   void ReadKeyboardInput();
   void ReadMouseInput();
   bool IsKeyDown( KeyCode keyCode ) const;

private:
   std::map<Button, ButtonState> _buttonStates;
   std::map<Button, std::vector<KeyCode>> _buttonKeyBindings;

   sf::Vector2i _mousePosition;
   sf::Vector2i _mousePreviousPosition;
   sf::Vector2i _mouseDelta;
};

NAMESPACE_END
