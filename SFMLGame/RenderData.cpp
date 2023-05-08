#include <SFML/Graphics/Texture.hpp>

#include "RenderData.h"
#include "EntitySprite.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

RenderData::RenderData( shared_ptr<GameClock> clock,
                        shared_ptr<Entity> player,
                        shared_ptr<Entity> npc )
{
   auto playerTexture = make_shared<Texture>();
   playerTexture->loadFromFile( "images/player_texture.png" );
   PlayerSprite = shared_ptr<EntitySprite>( new EntitySprite( clock,
                                                              player,
                                                              playerTexture,
                                                              Vector2i( 50, 50 ),  // frame dimensions
                                                              12,                  // total moving frames
                                                              0.05f ) );           // seconds per frame

   auto npcTexture = make_shared<Texture>();
   npcTexture->loadFromFile( "images/npc_texture_01.png" );
   NpcSprite = shared_ptr<EntitySprite>( new EntitySprite( clock,
                                                           npc,
                                                           npcTexture,
                                                           Vector2i( 50, 50 ),  // frame dimensions
                                                           12,                  // total moving frames
                                                           0.05f ) );           // seconds per frame
}
