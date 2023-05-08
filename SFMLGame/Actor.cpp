#include "Actor.h"
#include "Behavior.h"

using namespace NAMESPACE;
using namespace std;

Actor::Actor( shared_ptr<UniqueNumberGenerator> uniqueNumberGenerator ) :
   Entity( uniqueNumberGenerator ),
   _behavior( nullptr )
{
}

void Actor::SetBehavior( shared_ptr<Behavior> behavior )
{
   _behavior = behavior;
}

void Actor::Tick()
{
   if ( _behavior )
   {
      _behavior->Tick();
   }
}
