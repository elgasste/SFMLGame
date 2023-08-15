#pragma once

#include "Common.h"
#include "IInputReader.h"
#include "ButtonState.h"
#include "KeyCode.h"

NAMESPACE_BEGIN

class GameConfig;

class KeyboardInputReader : public IInputReader
{
public:
   KeyboardInputReader( std::shared_ptr<GameConfig> gameConfig );

   // IInputReader
   void ReadInput() override;
   bool WasButtonPressed( Button button ) const override;
   bool IsButtonDown( Button button ) const override;
   bool WasAnyButtonPressed() const override;

private:
   bool IsKeyDown( KeyCode keyCode ) const;

private:
   std::map<Button, ButtonState> _buttonStates;
   std::map<Button, std::vector<KeyCode>> _buttonKeyBindings;
};

NAMESPACE_END
