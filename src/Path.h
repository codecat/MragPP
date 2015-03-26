#ifndef MRAGPP_PATH_H_INCLUDED
#define MRAGPP_PATH_H_INCLUDED

#include "StdH.h"

MRAGPP_NAMESPACE_BEGIN;

class CPaths;

class MRAGPP_EXPORT CPath
{
  friend class CPaths;

private:
  bool p_bReady;
  CPaths* p_pPaths;

public:
  Vector2f p_vPos1;
  Vector2f p_vPos2;
  Vector2f p_vBezierAnchor;

  bool p_bBezier;

  int p_iCurrentFrameCount;
  int p_iTotalFrameCount;

  mragPathsOnUpdateFunction p_pOnUpdate;
  mragPathsOnFinishFunction p_pOnFinish;
  mragEasingFunction p_pUseEasing;

public:
  CPath();
  ~CPath();

  float GetNonSmoothedDelta();
  float GetCurrentDelta();

  Vector2f GetCurrentPosition();

  void SetTime(int iFrameCount);
  void SetTime(float fSeconds);

  void Swap();
  void Reset();

private:
  void Update();
  void Render();
};

MRAGPP_NAMESPACE_END;

#endif
