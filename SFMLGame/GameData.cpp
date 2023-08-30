#include "GameData.h"

using namespace NAMESPACE;
using namespace std;

GameData::GameData( shared_ptr<vector<Sector>> sectors,
                    BspNode* bspRootNode,
                    shared_ptr<Entity> player ) :
   _sectors( sectors ),
   _bspRootNode( bspRootNode ),
   _player( player )
{
}

GameData::~GameData()
{
   DeleteBspTreeRecursive( _bspRootNode );
}

void GameData::DeleteBspTreeRecursive( BspNode* node )
{
   if ( node == nullptr )
   {
      return;
   }

   if ( node->isLeaf )
   {
      delete node->subsector;
      node->subsector = nullptr;

      delete node;
      node = nullptr;
   }
   else
   {
      DeleteBspTreeRecursive( node->leftChild );
      DeleteBspTreeRecursive( node->rightChild );
   }
}
