#include "CommandAggregator.h"
#include "ICommandExecutor.h"

using namespace NAMESPACE;

void CommandAggregator::ExecuteCommand( GameCommand command, void* args )
{
   _executor->ExecuteCommand( command, args );
}
