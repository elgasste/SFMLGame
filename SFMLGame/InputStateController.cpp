#include "InputStateController.h"
#include "GameConfig.h"
#include "RenderConfig.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

InputStateController::InputStateController( shared_ptr<GameConfig> gameConfig ) :
   _gameConfig( gameConfig )
{
   for ( int i = 0; i < (int)Button::ButtonCount; i++ )
   {
      _buttonStates[(Button)i] = { false, false };
   }

   _mousePosition = Mouse::getPosition();
   _mousePreviousPosition = _mousePosition;
   _mouseDelta = Vector2i( 0, 0 );
}

void InputStateController::KeyPressed( Keyboard::Key key )
{
   if ( _gameConfig->KeyBindingsMap.contains( key ) )
   {
      auto button = _gameConfig->KeyBindingsMap.at( key );
      auto& buttonState = _buttonStates.at( button );

      buttonState.WasPressed = true;
      buttonState.IsDown = true;
   }
}

void InputStateController::KeyReleased( Keyboard::Key key )
{
   if ( _gameConfig->KeyBindingsMap.contains( key ) )
   {
      auto button = _gameConfig->KeyBindingsMap.at( key );
      auto& buttonState = _buttonStates.at( button );

      buttonState.WasPressed = false;
      buttonState.IsDown = false;
   }
}

void InputStateController::UpdateKeyStates()
{
   for ( const auto& [key, button] : _gameConfig->KeyBindingsMap )
   {
      // this means the key is still down after the initial press
      if ( Keyboard::isKeyPressed( key ) )
      {
         _buttonStates.at( button ).WasPressed = false;
      }
   }
}

void InputStateController::ReadMouseInput()
{
   _mousePreviousPosition.x = _mousePosition.x;
   _mousePreviousPosition.y = _mousePosition.y;

   _mousePosition.x = Mouse::getPosition().x;
   _mousePosition.y = Mouse::getPosition().y;

   _mouseDelta.x = _mousePosition.x - _mousePreviousPosition.x;
   _mouseDelta.y = _mousePosition.y - _mousePreviousPosition.y;
}

bool InputStateController::WasButtonPressed( Button button ) const
{
   return _buttonStates.at( button ).WasPressed;
}

bool InputStateController::IsButtonDown( Button button ) const
{
   return _buttonStates.at( button ).IsDown;
}

bool InputStateController::WasAnyButtonPressed() const
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
