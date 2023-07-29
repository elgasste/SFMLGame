#include "GameData.h"

using namespace NAMESPACE;
using namespace std;

GameData::GameData( vector<Sector> sectors,
                    shared_ptr<Entity> player ) :
   _sectors( sectors ),
   _player( player )
{
}
