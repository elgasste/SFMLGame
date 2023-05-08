#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class StringUtilities
{
public:
   static std::vector<std::string> Explode( const std::string& subject, char delimiter );
   static std::vector<std::string> ExplodeByWhitespace( const std::string& subject );
   static std::string ToUpper( const std::string& subject );
};

NAMESPACE_END
