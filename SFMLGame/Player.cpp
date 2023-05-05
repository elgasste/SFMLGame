#include "Player.h"
#include "GameData.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

Player::Player( shared_ptr<UniqueNumberGenerator> uniqueNumberGenerator,
                shared_ptr<GameData> gameData ) :
   Entity( uniqueNumberGenerator )
{
   _hitBox = gameData->PlayerHitBox;
   _position = gameData->PlayerDefaultPosition;
   _direction = gameData->PlayerDefaultDirection;
}
