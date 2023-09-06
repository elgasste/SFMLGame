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

   DefaultPlayerPosition = { 960, 540 };
   DefaultPlayerDirection = Direction::Down;
   MaximumPlayerVelocity = 5000;
   PlayerHitBoxWidth = 75;    // should match SpriteScalar
   PlayerHitBoxHeight = 115;  // should match SpriteScalar
   PlayerVelocityIncrement = 300;
}
