#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class __declspec( novtable ) IGameStateRenderer
{
public:
   virtual void Render() = 0;
};

NAMESPACE_END
