#include "GameConfig.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace sf;

GameConfig::GameConfig()
{
   KeyBindingsMap =
   {
      { Keyboard::Escape, Button::Back },
      { Keyboard::Enter, Button::Action },
      { Keyboard::Left, Button::Left },
      { Keyboard::Up, Button::Up },
      { Keyboard::Right, Button::Right },
      { Keyboard::Down, Button::Down },
      { Keyboard::F12, Button::Diagnostics },
   };

   ShowDiagnostics = false;

   DefaultBallPosition = { 960, 540 };
   DefaultBallAngle = RAD_45;
   DefaultBallVelocity = 600;
   MinimumBallVelocity = 60;
   MaximumBallVelocity = 5000;
   BallDiameter = 100;

   BallTurnAngleIncrement = 3;
   BallVelocityIncrement = 400;
}
