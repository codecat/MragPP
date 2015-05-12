#include "StdH.h"
#include "Path.h"
#include "Paths.h"

MRAGPP_NAMESPACE_BEGIN;

CPath::CPath()
{
  p_bReady = false;
  p_pPaths = 0;
  p_bBezier = false;
  p_iCurrentFrameCount = 0;
  p_iTotalFrameCount = 0;
  p_pOnUpdate = 0;
  p_pOnFinish = 0;
  p_pUseEasing = 0;
}

CPath::~CPath()
{

}

float CPath::GetNonSmoothedDelta()
{
  return (float)p_iCurrentFrameCount / (float)p_iTotalFrameCount;
}

float CPath::GetCurrentDelta()
{
  float x = GetNonSmoothedDelta();
  if(p_pUseEasing != 0) {
    x = p_pUseEasing(x);
  }
  return x;
}

Vector2f CPath::GetCurrentPosition()
{
  float x = GetCurrentDelta();
  if(p_bBezier) {
    if(x == 0) {
      return p_vPos1;
    } else if(x == 1) {
      return p_vPos2;
    } else {
      Vector2f v1 = mthLerp(p_vPos1, p_vBezierAnchor, x);
      Vector2f v2 = mthLerp(p_vBezierAnchor, p_vPos2, x);

      return mthLerp(v1, v2, x);
    }
  } else {
    return mthLerp(p_vPos1, p_vPos2, x);
  }
}

void CPath::SetTime(int iFrameCount)
{
  if(iFrameCount == p_iTotalFrameCount) {
    return;
  }

  float fDelta = GetNonSmoothedDelta();
  p_iTotalFrameCount = iFrameCount;
  p_iCurrentFrameCount = mthRound(fDelta * (float)p_iTotalFrameCount);
}

void CPath::SetTime(float fSeconds)
{
  SetTime((int)ceil(fSeconds / 0.0166667f));
}

void CPath::Swap()
{
  Vector2f vPosTemp = p_vPos1;
  p_vPos1 = p_vPos2;
  p_vPos2 = vPosTemp;
}

void CPath::Reset()
{
  if(!p_pPaths->ps_aPaths.ContainsPointer(this)) {
    p_pPaths->ps_aPaths.Push(this);
  }

  p_bReady = false;
  p_iCurrentFrameCount = 0;
}

void CPath::Update()
{
  p_iCurrentFrameCount++;

  if(p_pOnUpdate != 0) {
    p_pOnUpdate(GetCurrentPosition(), *this);
  }

  if(p_iCurrentFrameCount >= p_iTotalFrameCount) {
    p_pPaths->ps_aPaths.PopAt(p_pPaths->ps_aPaths.FindPointer(this));
    p_pPaths->ps_iIterator--;

    if(p_pOnFinish != 0) {
      p_pOnFinish(*this);
    }

    if(p_bReady) {
      delete this;
    }
  }
}

void CPath::Render()
{
  // TODO: Debug draw
}

MRAGPP_NAMESPACE_END;
