#include "CommandAggregator.h"
#include "ICommandExecutor.h"

using namespace NAMESPACE;

void CommandAggregator::ExecuteCommand( GameCommand command, void* arg )
{
   _executor->ExecuteCommand( command, arg );
}
