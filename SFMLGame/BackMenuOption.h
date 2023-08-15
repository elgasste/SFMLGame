#pragma once

#include "Common.h"
#include "IMenuOption.h"

NAMESPACE_BEGIN

class GameData;

class BackMenuOption : public IMenuOption
{
public:
   BackMenuOption( std::shared_ptr<GameData> gameData );

   // IMenuOption
   std::string GetText() const override { return _text; }
   void Select() override;

private:
   std::shared_ptr<GameData> _gameData;

   std::string _text;
};

NAMESPACE_END
