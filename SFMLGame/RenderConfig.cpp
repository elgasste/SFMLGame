#include "RenderConfig.h"
#include "GameConfig.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace std;

RenderConfig::RenderConfig( shared_ptr<GameConfig> gameConfig )
{
   FovAngle = RAD_30 * 2.0f;
   FovAngleIncrement = FovAngle / gameConfig->ScreenWidth;

   WallHeight = 100.0f;
   ProjectionPlaneDelta = gameConfig->ScreenHeight / 1.5f;
   LightingScalar = 2.0f;
}
