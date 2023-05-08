#pragma once

#include "Common.h"
#include "GameCommand.h"

NAMESPACE_BEGIN

class ICommandExecutor;

class CommandAggregator
{
public:
   void RegisterExecutor( ICommandExecutor* executor ) { _executor = executor; }
   void ExecuteCommand( GameCommand command, void* args );

private:
   ICommandExecutor* _executor;
};

NAMESPACE_END
