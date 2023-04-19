#pragma once

#include "Common.h"
#include "GameCommand.h"

NAMESPACE_BEGIN

class __declspec( novtable ) ICommandExecutor
{
public:
   virtual void ExecuteCommand( GameCommand command, void* arg ) = 0;
};

NAMESPACE_END
