#pragma once

#include "Common.h"
#include "IGameStateInputHandler.h"

NAMESPACE_BEGIN

class InputReader;
class GameConfig;
class GameData;
class GameClock;
class EventAggregator;

class PlayingStateInputHandler : public IGameStateInputHandler
{
public:
   PlayingStateInputHandler( std::shared_ptr<InputReader> inputReader,
                             std::shared_ptr<GameConfig> gameConfig,
                             std::shared_ptr<GameData> gameData,
                             std::shared_ptr<GameClock> clock,
                             std::shared_ptr<EventAggregator> eventAggregator );

   // IGameStateInputHandler
   void HandleInput() override;

private:
   std::shared_ptr<InputReader> _inputReader;
   std::shared_ptr<GameConfig> _gameConfig;
   std::shared_ptr<GameData> _gameData;
   std::shared_ptr<GameClock> _clock;
   std::shared_ptr<EventAggregator> _eventAggregator;
};

NAMESPACE_END
