#pragma once

#include "Common.h"
#include "Button.h"
#include "ButtonState.h"
#include "KeyCode.h"

NAMESPACE_BEGIN

class GameConfig;

class InputReader
{
public:
   InputReader( std::shared_ptr<GameConfig> gameConfig );

   // IInputReader
   void ReadInput();
   bool WasButtonPressed( Button button ) const;
   bool IsButtonDown( Button button ) const;
   bool WasAnyButtonPressed() const;

private:
   bool IsKeyDown( KeyCode keyCode ) const;

private:
   std::map<Button, ButtonState> _buttonStates;
   std::map<Button, std::vector<KeyCode>> _buttonKeyBindings;
};

NAMESPACE_END
