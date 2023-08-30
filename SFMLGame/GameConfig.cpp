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
      { KeyCode::Tab, Button::AutoMapToggle },
      { KeyCode::F12, Button::Diagnostics }
   };

   DefaultPlayerPosition = Vector2f( 320, 250 );
   DefaultPlayerAngle = RAD_90;

   MaxPlayerVelocity = 180.0f;
   PlayerVelocityAcceleration = 950.0f;
   PlayerVelocityDeceleration = 350.0f;

   MouseMoveAngleIncrement = 0.0006f;
   KeyboardTurnAngleIncrement = 0.02f;
   KeyboardMoveIncrement = 0.8f;
}
