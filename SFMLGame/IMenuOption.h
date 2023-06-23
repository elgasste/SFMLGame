#pragma once

#include <string>

#include "Common.h"

NAMESPACE_BEGIN

class __declspec( novtable ) IMenuOption
{
public:
   virtual std::string GetText() const = 0;
   virtual void Select() = 0;
};

NAMESPACE_END
