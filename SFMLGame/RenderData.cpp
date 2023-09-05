#include "RenderData.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

RenderData::RenderData( shared_ptr<sf::Texture> playerSpriteTexture ) :
   _playerSpriteTexture( playerSpriteTexture )
{
}
