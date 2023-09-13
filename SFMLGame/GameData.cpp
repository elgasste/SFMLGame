#include "GameData.h"

using namespace NAMESPACE;
using namespace std;

GameData::GameData( shared_ptr<vector<Linedef>> linedefs,
                    BspNode* rootBspNode,
                    shared_ptr<Entity> player ) :
   _linedefs( linedefs ),
   _rootBspNode( rootBspNode ),
   _player( player )
{
}

GameData::~GameData()
{
   DeleteBspNodeRecursive( _rootBspNode );
}

void GameData::DeleteBspNodeRecursive( BspNode* node )
{
   if ( node != nullptr )
   {
      DeleteBspNodeRecursive( node->leftChild );
      DeleteBspNodeRecursive( node->rightChild );
      delete node;
      node = nullptr;
   }
}
