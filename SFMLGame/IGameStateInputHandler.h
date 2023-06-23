#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class __declspec( novtable ) IGameStateInputHandler
{
public:
   virtual void HandleInput() = 0;
};

NAMESPACE_END
