#pragma once

#include <map>
#include <vector>
#include <SFML/System/Vector2.hpp>

#include "Common.h"
#include "IInputReader.h"
#include "ButtonState.h"
#include "KeyCode.h"

NAMESPACE_BEGIN

class GameConfig;

class InputReader
{
public:
   InputReader( std::shared_ptr<GameConfig> gameConfig );

   void ReadInput();
   bool WasButtonPressed( Button button ) const;
   bool IsButtonDown( Button button ) const;
   bool WasAnyButtonPressed() const;
   sf::Vector2i GetMouseDelta() const { return _mouseDelta; }

private:
   bool IsKeyDown( KeyCode keyCode ) const;
   void ReadKeyboardInput();
   void ReadMouseInput();

private:
   std::map<Button, ButtonState> _buttonStates;
   std::map<Button, std::vector<KeyCode>> _buttonKeyBindings;

   sf::Vector2i _mouseCenterPoint;
   sf::Vector2i _mouseDelta;
};

NAMESPACE_END
