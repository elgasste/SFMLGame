#include "RectUtilities.h"

using namespace NAMESPACE;
using namespace sf;

bool RectUtilities::ClampRectToBounds( Vector2f& position, const FloatRect& rect, const FloatRect& bounds )
{
   bool clamped = false;

   if ( position.x < bounds.left )
   {
      position.x = bounds.left;
      clamped = true;
   }
   else if ( ( position.x + rect.width ) > ( bounds.left + bounds.width ) )
   {
      position.x = bounds.left + bounds.width - rect.width;
      clamped = true;
   }

   if ( position.y < bounds.top )
   {
      position.y = bounds.top;
      clamped = true;
   }
   else if ( ( position.y + rect.height ) > ( bounds.top + bounds.height ) )
   {
      position.y = bounds.top + bounds.height - rect.height;
      clamped = true;
   }

   return clamped;
}
