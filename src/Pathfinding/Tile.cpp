#include "../StdH.h"
#include "Tile.h"

MRAGPP_NAMESPACE_BEGIN;

CPathFindingTile::CPathFindingTile()
{
  til_iID = 0;
  til_bSolid = false;
  til_bStart = false;
  til_bEnd = false;
}

CPathFindingTile::CPathFindingTile(Vector2i vPosition, int iNewID)
{
  til_vPosition = vPosition;
  til_iID = iNewID;
  til_bSolid = false;
  til_bStart = false;
  til_bEnd = false;
}

CPathFindingTile::~CPathFindingTile()
{
}

MRAGPP_NAMESPACE_END;
