#include "RenderData.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

RenderData::RenderData( shared_ptr<map<int, Texture>> textureMap,
                        shared_ptr<map<int, Sprite>> spriteMap ) :
   _textureMap( textureMap ),
   _spriteMap( spriteMap )
{
}
