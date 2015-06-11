#include "../StdH.h"
#include "Pathfinding.h"

using namespace Scratch;

MRAGPP_NAMESPACE_BEGIN;

CPathFinding::CPathFinding()
{
  pth_bDiagonal = false;
  pth_pnodStart = 0;
  pth_pnodEnd = 0;
  pth_pnodCurrent = 0;
  pth_iAddCounter = 0;
}

CPathFinding::CPathFinding(int width, int height)
{
  pth_bDiagonal = false;
  pth_pnodStart = 0;
  pth_pnodEnd = 0;
  pth_pnodCurrent = 0;
  pth_iAddCounter = 0;
  SetSize(width, height);
}

CPathFinding::~CPathFinding()
{
  if(pth_pnodEnd != 0) {
    delete pth_pnodEnd;
  }
}

void CPathFinding::SetSize(int width, int height)
{
  pth_vMapSize(1) = width;
  pth_vMapSize(2) = height;
}

void CPathFinding::AddTile(const Vector2i &vPos, bool bSolid)
{
  CPathFindingTile &tile = pth_saTiles.Push();
  tile.til_vPosition = vPos;
  tile.til_bSolid = bSolid;
  tile.til_iID = pth_iAddCounter++;
}

bool CPathFinding::FindPath(StackArray<Vector2i> &ret, const Vector2i &vStart, const Vector2i &vEnd, int iMaxTiles)
{
  ASSERT(ret.Count() == 0);

  pth_saOpenList.Clear();
  pth_saClosedList.Clear();

  if(pth_saTiles.Count() == 0) {
    // nothing to do
    ASSERT(FALSE);
    return false;
  }

  if(vStart == vEnd) {
    // nothing to do
    return false;
  }

  for(int i=0; i<pth_saTiles.Count(); i++) {
    if(pth_saTiles[i].til_vPosition == vStart) {
      pth_pnodStart = &pth_saOpenList.Push();
      pth_pnodStart->nod_iCellIndex = pth_saTiles[i].til_iID;
      pth_saTiles[i].til_bStart = true;
    } else if(pth_saTiles[i].til_vPosition == vEnd) {
      pth_pnodEnd = new CPathFindingNode;
      pth_pnodEnd->nod_iCellIndex = pth_saTiles[i].til_iID;
      pth_saTiles[i].til_bEnd = true;
    }
  }

  ASSERT(pth_pnodStart != 0);
  ASSERT(pth_pnodEnd != 0);

  bool bFound = false;

  while(pth_saOpenList.Count() > 0) {
    pth_pnodCurrent = FindSmallestF();
    if(pth_pnodCurrent == 0) {
      ASSERT(FALSE);
      break;
    }

    if(pth_pnodCurrent->nod_iCellIndex == pth_pnodEnd->nod_iCellIndex) {
      bFound = true;
      break;
    }

    pth_saOpenList.PopAt(pth_saOpenList.FindPointer(pth_pnodCurrent));
    pth_saClosedList.Push(pth_pnodCurrent);

    if(pth_bDiagonal) {
      AddAdjacentCellToOpenList(pth_pnodCurrent, 1, -1, 14);
      AddAdjacentCellToOpenList(pth_pnodCurrent, -1, -1, 14);
      AddAdjacentCellToOpenList(pth_pnodCurrent, -1, 1, 14);
      AddAdjacentCellToOpenList(pth_pnodCurrent, 1, 1, 14);
    }
    AddAdjacentCellToOpenList(pth_pnodCurrent, 0, -1, 14);
    AddAdjacentCellToOpenList(pth_pnodCurrent, -1, 0, 14);
    AddAdjacentCellToOpenList(pth_pnodCurrent, 1, 0, 14);
    AddAdjacentCellToOpenList(pth_pnodCurrent, 0, 1, 14);
  }

  while(pth_pnodCurrent != 0) {
    if(pth_pnodStart->nod_iCellIndex == pth_pnodCurrent->nod_iCellIndex) {
      break;
    }
    ret.PushBegin() = pth_saTiles[pth_pnodCurrent->nod_iCellIndex].til_vPosition;
    pth_pnodCurrent = pth_pnodCurrent->nod_pParent;
  }

  return bFound;
}

CPathFindingNode* CPathFinding::FindSmallestF()
{
  int smallestF = 999999; // eh.
  CPathFindingNode* ret = 0;

  for(int i=0; i<pth_saOpenList.Count(); i++) {
    CPathFindingNode &node = pth_saOpenList[i];
    if(node.nod_iF < smallestF) {
      ret = &node;
      smallestF = node.nod_iF;
    }
  }

  return ret;
}

void CPathFinding::AddAdjacentCellToOpenList(CPathFindingNode* parentNode, int columnOffset, int rowOffset, int gCost)
{
  ASSERT(parentNode != 0);

  int adjacentCellIndex = GetAdjacentCellIndex(parentNode->nod_iCellIndex, columnOffset, rowOffset);

  // ignore unwalkable nodes (or nodes outside the grid)
  if(adjacentCellIndex == -1) {
    return;
  }

  // ignore nodes on the closed list
  if(pth_saClosedList.ContainsAny([=](CPathFindingNode &node) { return node.nod_iCellIndex == adjacentCellIndex; })) {
    return;
  }

  int iAdjacentNodeIndex = pth_saOpenList.FindAny([=](CPathFindingNode &node) { return node.nod_iCellIndex == adjacentCellIndex; });
  if(iAdjacentNodeIndex != -1) {
    CPathFindingNode &adjacentNode = pth_saOpenList[iAdjacentNodeIndex];
    if(parentNode->nod_iG + gCost < adjacentNode.nod_iG) {
      adjacentNode.nod_pParent = parentNode;
      adjacentNode.nod_iG = parentNode->nod_iG + gCost;
      adjacentNode.nod_iF = adjacentNode.nod_iG + adjacentNode.nod_iH;
    }
    return;
  }

  CPathFindingNode &newNode = pth_saOpenList.Push();
  newNode.nod_iCellIndex = adjacentCellIndex;
  newNode.nod_pParent = parentNode;
  newNode.nod_iG = gCost;
  newNode.nod_iH = GetDistance(adjacentCellIndex, pth_pnodEnd->nod_iCellIndex);
  newNode.nod_iF = newNode.nod_iG + newNode.nod_iH;
}

int CPathFinding::GetAdjacentCellIndex(int cellIndex, int columnOffset, int rowOffset)
{
  int x = cellIndex % pth_vMapSize(1);
  int y = cellIndex / pth_vMapSize(1);

  if((x + columnOffset < 0 || x + columnOffset > pth_vMapSize(1) - 1) ||
     (y + rowOffset < 0 || y + rowOffset > pth_vMapSize(2) - 1)) {
    return -1;
  }

  if(pth_saTiles[((y + rowOffset) * pth_vMapSize(1)) + (x + columnOffset)].til_bSolid) {
    return -1;
  }

  return cellIndex + columnOffset + (rowOffset * pth_vMapSize(1));
}

int CPathFinding::GetDistance(int startTileID, int endTileID)
{
  CPathFindingTile &tileStart = pth_saTiles[startTileID];
  int startX = tileStart.til_vPosition(1) / pth_vMapSize(1);
  int startY = tileStart.til_vPosition(2) / pth_vMapSize(2);

  CPathFindingTile &tileEnd = pth_saTiles[endTileID];
  int endX = tileEnd.til_vPosition(1) / pth_vMapSize(1);
  int endY = tileEnd.til_vPosition(2) / pth_vMapSize(2);

  return mthAbs(startX - endX) + mthAbs(startY - endY);
}

MRAGPP_NAMESPACE_END;
