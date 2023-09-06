#pragma once

#include "Common.h"
#include "IGameStateInputHandler.h"
#include "Direction.h"

NAMESPACE_BEGIN

class InputReader;
class GameConfig;
class EventQueue;

class PlayingStateInputHandler : public IGameStateInputHandler
{
public:
   PlayingStateInputHandler( std::shared_ptr<InputReader> inputReader,
                             std::shared_ptr<GameConfig> gameConfig,
                             std::shared_ptr<EventQueue> eventQueue );

   // IGameStateInputHandler
   void HandleInput() override;

private:
   void CacheDirectionInput();

private:
   std::shared_ptr<InputReader> _inputReader;
   std::shared_ptr<GameConfig> _gameConfig;
   std::shared_ptr<EventQueue> _eventQueue;

   bool _isLeftDown;
   bool _isUpDown;
   bool _isRightDown;
   bool _isDownDown;
   bool _directionWasPressedLastFrame;
   Direction _directionCache;
};

NAMESPACE_END
