#include "GameData.h"
#include "GameConfig.h"
#include "Actor.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

// MUFFINS: the initialization of this data should go into GameLoader.
// also, maybe this class should "own" everything? including the player and arena?
GameData::GameData( shared_ptr<GameConfig> config,
                    shared_ptr<UniqueNumberGenerator> uniqueNumberGenerator )
{
   ArenaBounds = FloatRect( 0, 0, (float)config->ScreenWidth, (float)config->ScreenHeight );

   PlayerHitBox = FloatRect( 0, 0, 100, 100 );
   PlayerDefaultPosition = Vector2f( ( ArenaBounds.width / 2 ) - ( PlayerHitBox.width / 2 ),
                                     ( ArenaBounds.height / 2 ) - ( PlayerHitBox.height / 2 ) );
   PlayerMoveVelocity = 400;
   PlayerDefaultDirection = Direction::Right;

   Npc = shared_ptr<Actor>( new Actor( uniqueNumberGenerator ) );
   Npc->SetHitBox( FloatRect( 0, 0, 100, 100 ) );
   Npc->SetPosition( Vector2f( 0, 0 ) );
}
