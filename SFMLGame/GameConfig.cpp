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
      { KeyCode::F12, Button::Diagnostics },
      { KeyCode::Tab, Button::Wireframe }
   };

   ShowDiagnostics = false;

   HitBoxBlockSize = 4;
   LinesegClipDistance = 0.5f;

   DefaultPlayerPosition = { 480, 320 };     // this will depend on the map data, eventually
   DefaultPlayerDirection = Direction::Down; // this will depend on the map data, eventually
   PlayerHitBoxWidth = 24;  // should be divisible by HitBoxBlockSize
   PlayerHitBoxHeight = 48; // should be divisible by HitBoxBlockSize
   PlayerVelocityIncrement = 150;
   PlayerVelocityDiagonalScalar = 0.70710678118f; // cos( 45 degrees )

   ShowWireframeMap = false;
}
