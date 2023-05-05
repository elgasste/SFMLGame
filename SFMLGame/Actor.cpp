#include "Actor.h"
#include "Behavior.h"

using namespace NAMESPACE;
using namespace std;

Actor::Actor( shared_ptr<UniqueNumberGenerator> uniqueNumberGenerator,
              shared_ptr<Behavior> behavior ) :
   Entity( uniqueNumberGenerator ),
   _behavior( behavior )
{
   behavior->SetEntity( this );
}

void Actor::Tick()
{
   _behavior->Tick();
}
