#pragma once

#include <vector>

#include "Common.h"
#include "Range.h"

NAMESPACE_BEGIN

class ColumnTracker
{
public:
   void Reset( int leftEdge, int rightEdge );
   void TrackRange( int start, int end );
   bool IsFullyTracked() const { return _untrackedRanges.empty(); }

   int GetUntrackedRangeCount() const { return (int)_untrackedRanges.size(); }
   int GetRangeStart( int index ) const { return _untrackedRanges.at( index ).start; }
   int GetRangeEnd( int index ) const { return _untrackedRanges.at( index ).end; }

private:
   std::vector<Range<int>> _untrackedRanges;
};

NAMESPACE_END
