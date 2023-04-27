#include <SFML/Graphics/Texture.hpp>

#include "RenderData.h"
#include "ActorSprite.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

RenderData::RenderData( shared_ptr<GameClock> clock,
                        shared_ptr<Actor> player )
{
   // MUFFINS: I guess we should take in a GameData and scale the sprite based on the player's hit box?
   auto playerTexture = make_shared<Texture>();
   playerTexture->loadFromFile( "images/player_texture.png" );
   PlayerSprite = shared_ptr<ActorSprite>( new ActorSprite( clock,
                                                            player,
                                                            playerTexture,
                                                            Vector2i( 50, 50 ),  // frame dimensions
                                                            6,                   // total moving frames
                                                            0.05f ) );            // seconds per frame
}
