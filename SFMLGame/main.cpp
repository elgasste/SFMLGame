#include <stdio.h>

#include "GameLoader.h"
#include "Game.h"

using namespace NAMESPACE;
using namespace std;

int main()
{
   printf( "Loading all the things..." );

   auto loader = make_shared<GameLoader>();
   auto game = loader->Load();

   printf( "done!\nHave fun in there!" );

   game->Run();

   printf( "\nSigning off, enjoy your burrito!\n\n" );

   return 0;
}