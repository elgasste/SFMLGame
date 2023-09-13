#pragma once

#include "Common.h"
#include "SubSector.h"

NAMESPACE_BEGIN

struct BspNode
{
   bool isLeaf;
   LineDef* lineDef;
   SubSector* subSector;
   BspNode* leftChild;
   BspNode* rightChild;
};

NAMESPACE_END
