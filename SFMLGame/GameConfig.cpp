#include <SFML/Window/WindowStyle.hpp>

#include "GameConfig.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

GameConfig::GameConfig()
{
   ScreenWidth = 1920;
   ScreenHeight = 1080;

   WindowTitle = "SFML Game";
   WindowStyle = Style::Titlebar | Style::Close;

   KeyBindingsMap =
   {
      { KeyCode::Escape, Button::Back },
      { KeyCode::Return, Button::Action },
      { KeyCode::Left, Button::Left },
      { KeyCode::Up, Button::Up },
      { KeyCode::Right, Button::Right },
      { KeyCode::Down, Button::Down },
      { KeyCode::W, Button::Forward },
      { KeyCode::S, Button::Backward },
      { KeyCode::A, Button::StrafeLeft },
      { KeyCode::D, Button::StrafeRight },
      { KeyCode::F12, Button::Diagnostics }
   };

   DefaultPlayerPosition = Vector2f( 320, 250 );
   DefaultPlayerRadius = 10.0f;
   DefaultPlayerAngle = RAD_90;

   MaxPlayerVelocity = 1.5f;
   PlayerVelocityAcceleration = 0.1f;
   PlayerVelocityDeceleration = 0.03f;

   MouseMoveAngleIncrement = 0.0006f;
   KeyboardTurnAngleIncrement = 0.02f;
   KeyboardMoveIncrement = 0.8f;
}
