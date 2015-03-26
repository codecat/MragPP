#include "../StdH.h"
#include "Node.h"

MRAGPP_NAMESPACE_BEGIN;

CPathFindingNode::CPathFindingNode()
{
  nod_pParent = 0;
  nod_iCellIndex = 0;
  nod_iF = 0;
  nod_iG = 0;
  nod_iH = 0;
}

CPathFindingNode::~CPathFindingNode()
{
}

MRAGPP_NAMESPACE_END;
