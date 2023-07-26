#pragma once

#include <vector>

#include "Common.h"
#include "Subsector.h"

NAMESPACE_BEGIN

struct BspNode
{
   BspNode* parent;
   BspNode* leftChild;
   BspNode* rightChild;

   bool isLeaf;
   Linedef* linedef;
   Subsector* subsector;
};

NAMESPACE_END
