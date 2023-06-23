#include "BackMenuOption.h"
#include "GameStateController.h"

using namespace NAMESPACE;
using namespace std;

BackMenuOption::BackMenuOption( shared_ptr<GameStateController> stateController ) :
   _stateController( stateController )
{
}

void BackMenuOption::Select()
{
   _stateController->SetState( GameState::Playing );
}
