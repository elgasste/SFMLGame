#include "GameConfig.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace std;

GameConfig::GameConfig()
{
   KeyBindingsMap =
   {
      { KeyCode::Escape, Button::Back },
      { KeyCode::Return, Button::Action },
      { KeyCode::Left, Button::Left },
      { KeyCode::Up, Button::Up },
      { KeyCode::Right, Button::Right },
      { KeyCode::Down, Button::Down },
      { KeyCode::F12, Button::Diagnostics }
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
