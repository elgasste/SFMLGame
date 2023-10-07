#include "GameConfig.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace std;
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
      { Keyboard::Tab, Button::Wireframe }
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
