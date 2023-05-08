#pragma once

#include "MbcVirtualMachine.h"

NAMESPACE_BEGIN

class GameClock;
class Random;
class Entity;

class Behavior : public MbcVirtualMachine
{
public:
   Behavior( std::shared_ptr<GameClock> clock,
             std::shared_ptr<Random> random,
             std::shared_ptr<Entity> player );

   void SetEntity( std::shared_ptr<Entity> entity );

private:
   bool HandleCommand( mbc_command command ) override;

   void RegisterFloatFromArg( int argNum, float val );
   void RegisterIntFromArg( int argNum, int val );
   void RegisterBoolFromArg( int argNum, bool val );

   void GetRandomFloat();
   void GetRandomInt();

private:
   std::shared_ptr<GameClock> _clock;
   std::shared_ptr<Random> _random;
   std::shared_ptr<Entity> _player;

   std::shared_ptr<Entity> _entity;
};

NAMESPACE_END
