#include "Player.h"
#include "GameData.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

Player::Player( shared_ptr<GameData> gameData )
{
   _hitBox = gameData->PlayerHitBox;
   _position = gameData->PlayerDefaultPosition;
   _direction = gameData->PlayerDefaultDirection;
}
