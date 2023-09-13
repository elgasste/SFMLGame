#include "GameData.h"

using namespace NAMESPACE;
using namespace std;

GameData::GameData( shared_ptr<vector<LineDef>> lineDefs,
                    shared_ptr<vector<SubSector>> subSectors,
                    BspNode* rootBspNode,
                    shared_ptr<Entity> player ) :
   _lineDefs( lineDefs ),
   _subSectors( subSectors ),
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
