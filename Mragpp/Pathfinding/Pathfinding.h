#ifndef MRAGPP_PATHFINDING_H_INCLUDED
#define MRAGPP_PATHFINDING_H_INCLUDED

#include "../StdH.h"
#include "Tile.h"
#include "Node.h"

MRAGPP_NAMESPACE_BEGIN;

// Ported from the following code base: https://bitbucket.org/kc3w/a-algorithm

class MRAGPP_EXPORT CPathFinding
{
public:
  Scratch::StackArray<CPathFindingTile> pth_saTiles;
  bool pth_bDiagonal;
  Vector2i pth_vMapSize;

private:
  Scratch::StackArray<CPathFindingNode> pth_saOpenList;
  Scratch::StackArray<CPathFindingNode> pth_saClosedList;
  CPathFindingNode* pth_pnodStart;
  CPathFindingNode* pth_pnodEnd;
  CPathFindingNode* pth_pnodCurrent;
  int pth_iAddCounter;

public:
  CPathFinding();
  CPathFinding(int width, int height);
  ~CPathFinding();

  void SetSize(int width, int height);
  void AddTile(const Vector2i &vPos, bool bSolid);
  bool FindPath(Scratch::StackArray<Vector2i> &ret, const Vector2i &vStart, const Vector2i &vEnd, int iMaxTiles = 0);

private:
  CPathFindingNode* FindSmallestF();
  void AddAdjacentCellToOpenList(CPathFindingNode* parentNode, int columnOffset, int rowOffset, int gCost);
  int GetAdjacentCellIndex(int cellIndex, int columnOffset, int rowOffset);
  int GetDistance(int startTileID, int endTileID);
};

MRAGPP_NAMESPACE_END;

#endif
