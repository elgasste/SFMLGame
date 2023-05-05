#include <SFML/Graphics/Texture.hpp>

#include "RenderData.h"
#include "EntitySprite.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

RenderData::RenderData( shared_ptr<GameClock> clock,
                        shared_ptr<Entity> player )
{
   auto playerTexture = make_shared<Texture>();
   playerTexture->loadFromFile( "images/player_texture.png" );
   PlayerSprite = shared_ptr<EntitySprite>( new EntitySprite( clock,
                                                              player,
                                                              playerTexture,
                                                              Vector2i( 50, 50 ),  // frame dimensions
                                                              12,                  // total moving frames
                                                              0.05f ) );           // seconds per frame
}
