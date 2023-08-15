#include "BackMenuOption.h"
#include "GameData.h"

using namespace NAMESPACE;
using namespace std;

BackMenuOption::BackMenuOption( shared_ptr<GameData> gameData ) :
   _gameData( gameData ),
   _text( IDS_MenuOptionBack )
{
}

void BackMenuOption::Select()
{
   _gameData->SetGameState( GameState::Playing );
}
