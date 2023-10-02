#include <stdio.h>

#include "GameLoader.h"
#include "Game.h"

using namespace NAMESPACE;
using namespace std;

int main()
{
   SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL );

   printf( IDS_LoadingMessage );

   auto loader = make_shared<GameLoader>();
   auto game = loader->Load();

   printf( IDS_DoneLoading );
   printf( "\n" );
   printf( IDS_HaveFun );

   game->Run();

   printf( "\n" );
   printf( IDS_GameClosed );
   printf( "\n\n" );

   return 0;
}