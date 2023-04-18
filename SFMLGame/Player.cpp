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

void Player::MoveX( float distanceX )
{
   _position.x += distanceX;
}

void Player::MoveY( float distanceY )
{
   _position.y += distanceY;
}
