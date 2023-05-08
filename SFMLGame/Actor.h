#pragma once

#include "Entity.h"

NAMESPACE_BEGIN

class UniqueNumberGenerator;
class Behavior;

class Actor : public Entity
{
public:
   Actor( std::shared_ptr<UniqueNumberGenerator> uniqueNumberGenerator );

   void SetBehavior( std::shared_ptr<Behavior> behavior );
   virtual void Tick();

private:
   std::shared_ptr<Behavior> _behavior;
};

NAMESPACE_END
