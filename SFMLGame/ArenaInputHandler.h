#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class GameData;
class IInputReader;
class Arena;

class ArenaInputHandler
{
public:
   ArenaInputHandler( std::shared_ptr<GameData> gameData,
                      std::shared_ptr<IInputReader> inputReader,
                      std::shared_ptr<Arena> arena );

   void HandleInput() const;

private:
   std::shared_ptr<GameData> _gameData;
   std::shared_ptr<IInputReader> _inputReader;
   std::shared_ptr<Arena> _arena;
};

NAMESPACE_END
