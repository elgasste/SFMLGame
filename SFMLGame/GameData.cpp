#include "GameData.h"

using namespace NAMESPACE;
using namespace std;

GameData::GameData( shared_ptr<Entity> ball ) :
   _gameState( (GameState)0 ),
   _ball( ball )
{
}
