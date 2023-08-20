#pragma once

#include "Common.h"
#include "IMenuOption.h"

NAMESPACE_BEGIN

class EventQueue;

class QuitMenuOption : public IMenuOption
{
public:
   QuitMenuOption( std::shared_ptr<EventQueue> eventQueue );

   // IMenuOption
   std::string GetText() const override { return _text; }
   void Select() override;

private:
   std::shared_ptr<EventQueue> _eventQueue;

   std::string _text;
};

NAMESPACE_END
