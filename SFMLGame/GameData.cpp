#include "GameData.h"
#include "GameConfig.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

GameData::GameData( shared_ptr<GameConfig> config )
{
   ArenaBounds = FloatRect( 0, 0, (float)config->ScreenWidth, (float)config->ScreenHeight );

   PlayerHitBox = FloatRect( 0, 0, 50, 50 );
   PlayerDefaultPosition = Vector2f( ( ArenaBounds.width / 2 ) - ( PlayerHitBox.width / 2 ),
                                     ( ArenaBounds.height / 2 ) - ( PlayerHitBox.height / 2 ) );
   PlayerMoveVelocity = 300;
   PlayerDefaultDirection = Direction::Right;
}
