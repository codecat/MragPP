#ifndef MRAGPP_PATHFINDING_NODE_H_INCLUDED
#define MRAGPP_PATHFINDING_NODE_H_INCLUDED

#include "../StdH.h"

MRAGPP_NAMESPACE_BEGIN;

class MRAGPP_EXPORT CPathFindingNode
{
public:
  CPathFindingNode* nod_pParent;
  int nod_iCellIndex;

  int nod_iF;
  int nod_iG;
  int nod_iH;

public:
  CPathFindingNode();
  ~CPathFindingNode();
};

MRAGPP_NAMESPACE_END;

#endif
