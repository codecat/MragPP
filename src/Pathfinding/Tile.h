#ifndef MRAGPP_PATHFINDING_TILE_H_INCLUDED
#define MRAGPP_PATHFINDING_TILE_H_INCLUDED

#include "../StdH.h"
#include "../Vector.h"

MRAGPP_NAMESPACE_BEGIN;

class MRAGPP_EXPORT CPathFindingTile
{
  friend class CPathFinding;
public:
  Vector2i til_vPosition;
  int til_iID;
  bool til_bSolid;

private:
  bool til_bStart;
  bool til_bEnd;

public:
  CPathFindingTile();
  CPathFindingTile(Vector2i vPosition, int iNewID);
  ~CPathFindingTile();
};

MRAGPP_NAMESPACE_END;

#endif
