#pragma once

#include "Common.h"
#include "Subsector.h"

NAMESPACE_BEGIN

struct BspNode
{
   bool isLeaf;
   Linedef* linedef;
   SubSector* subsector;
   BspNode* leftChild;
   BspNode* rightChild;
};

NAMESPACE_END
