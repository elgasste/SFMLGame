#pragma once

#include <vector>

#include "Common.h"
#include "Lineseg.h"

NAMESPACE_BEGIN

struct BspNode
{
   BspNode* Parent;
   BspNode* LeftChild;
   BspNode* RightChild;

   bool IsLeaf;
   Linedef* linedef;
   std::vector<Lineseg> Linesegs;
};

NAMESPACE_END
