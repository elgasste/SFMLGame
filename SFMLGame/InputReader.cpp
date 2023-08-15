#include "SFML/Window/Mouse.hpp"

#include "WindowsLibs.h"

#include "InputReader.h"
#include "GameConfig.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

InputReader::InputReader( shared_ptr<GameConfig> gameConfig )
{
   for ( int i = 0; i < (int)Button::ButtonCount; i++ )
   {
      _buttonStates[(Button)i] = { false, false };
   }

   // since we allow multiple keys to bind to a single button, creating this inverted
   // map of button-to-keys makes the input reading logic much easier
   for ( int i = 0; i < (int)Button::ButtonCount; i++ )
   {
      auto button = (Button)i;

      for ( auto const& [keyCode, mappedButton] : gameConfig->KeyBindingsMap )
      {
         if ( mappedButton == button )
         {
            _buttonKeyBindings[button].push_back( keyCode );
         }
      }
   }

   _mouseCenterPoint = Vector2i( gameConfig->ScreenWidth / 2, gameConfig->ScreenHeight / 2 );
}

void InputReader::ReadInput()
{
   ReadKeyboardInput();
   ReadMouseInput();
}

bool InputReader::WasButtonPressed( Button button ) const
{
   return _buttonStates.at( button ).WasPressed;
}

bool InputReader::IsButtonDown( Button button ) const
{
   return _buttonStates.at( button ).IsDown;
}

bool InputReader::WasAnyButtonPressed() const
{
   for ( int i = 0; i < (int)Button::ButtonCount; i++ )
   {
      auto button = (Button)i;

      if ( button != Button::Diagnostics && WasButtonPressed( button ) )
      {
         return true;
      }
   }

   return false;
}

bool InputReader::IsKeyDown( KeyCode keyCode ) const
{
   // if the high-order bit is 1, the key is down
   return GetKeyState( (int)keyCode ) & 0x800;
}

void InputReader::ReadKeyboardInput()
{
   for ( auto const& [button, keyCodes] : _buttonKeyBindings )
   {
      bool buttonIsDown = false;

      for ( const auto& keyCode : keyCodes )
      {
         if ( IsKeyDown( keyCode ) )
         {
            buttonIsDown = true;
            break;
         }
      }

      if ( buttonIsDown )
      {
         _buttonStates.at( button ).WasPressed = !_buttonStates.at( button ).IsDown;
         _buttonStates.at( button ).IsDown = true;
      }
      else
      {
         _buttonStates.at( button ).WasPressed = false;
         _buttonStates.at( button ).IsDown = false;
      }
   }
}

void InputReader::ReadMouseInput()
{
   _mouseDelta.x = Mouse::getPosition().x - _mouseCenterPoint.x;
   _mouseDelta.y = Mouse::getPosition().y - _mouseCenterPoint.y;

   Mouse::setPosition( _mouseCenterPoint );
}
