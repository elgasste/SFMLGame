#pragma once

#include "Common.h"
#include "IMenuOption.h"

NAMESPACE_BEGIN

class GameStateController;

class BackMenuOption : public IMenuOption
{
public:
   BackMenuOption( std::shared_ptr<GameStateController> stateController );

   // IMenuOption
   std::string GetText() const override { return _text; }
   void Select() override;

private:
   std::shared_ptr<GameStateController> _stateController;

   std::string _text;
};

NAMESPACE_END
