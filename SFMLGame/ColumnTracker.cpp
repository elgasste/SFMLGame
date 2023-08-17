#include "ColumnTracker.h"

using namespace NAMESPACE;
using namespace std;

void ColumnTracker::Reset( int leftEdge, int rightEdge )
{
   _untrackedRanges.clear();
   _untrackedRanges.push_back( { leftEdge, rightEdge } );
}

void ColumnTracker::TrackRange( int start, int end )
{
   for ( int i = 0; i < (int)_untrackedRanges.size(); i++ )
   {
      auto& untrackedRange = _untrackedRanges[i];

      if ( end < untrackedRange.start )
      {
         // the list is ordered left to right, so we don't need to check further
         return;
      }
      else if ( start > untrackedRange.end )
      {
         continue;
      }

      if ( start > untrackedRange.start )
      {
         auto originalEnd = untrackedRange.end;
         untrackedRange.end = start - 1;

         if ( end < originalEnd )
         {
            _untrackedRanges.insert( _untrackedRanges.begin() + i + 1, { end + 1, originalEnd } );
         }
      }
      else
      {
         if ( end < untrackedRange.end )
         {
            untrackedRange.start = end + 1;
         }
         else
         {
            _untrackedRanges.erase( _untrackedRanges.begin() + i );
            i--;
         }
      }
   }
}
