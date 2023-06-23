#pragma once

#include "Common.h"
#include "IMenuOption.h"

NAMESPACE_BEGIN

class EventAggregator;

class QuitMenuOption : public IMenuOption
{
public:
   QuitMenuOption( std::shared_ptr<EventAggregator> eventAggregator );

   // IMenuOption
   std::string GetText() const override { return _text; }
   void Select() override;

private:
   std::shared_ptr<EventAggregator> _eventAggregator;

   std::string _text;
};

NAMESPACE_END
