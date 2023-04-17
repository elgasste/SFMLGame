#pragma once

#include "Common.h"
#include "Button.h"

NAMESPACE_BEGIN

class __declspec( novtable ) IInputReader
{
public:
   virtual void ReadInput() = 0;
   virtual bool WasButtonPressed( Button button ) const = 0;
   virtual bool IsButtonDown( Button button ) const = 0;
   virtual bool WasAnyButtonPressed() const = 0;
};

NAMESPACE_END
