#ifndef MRAGPP_PATHS_H_INCLUDED
#define MRAGPP_PATHS_H_INCLUDED

#include "StdH.h"
#include "Path.h"

MRAGPP_NAMESPACE_BEGIN;

class MRAGPP_EXPORT CPaths
{
  friend class CPath;

private:
  int ps_iIterator;
  Scratch::CStackArray<CPath> ps_aPaths;

public:
  CPaths();
  ~CPaths();

  CPath& Create(const Vector2f &vPos1, const Vector2f &vPos2, int iTotalFrameCount,
    mragPathsOnUpdateFunction onUpdate, mragPathsOnFinishFunction onFinish = 0);
  CPath& Create(const Vector2f &vPos1, const Vector2f &vPos2, float fSeconds,
    mragPathsOnUpdateFunction onUpdate, mragPathsOnFinishFunction onFinish = 0);

  void Update();
  void Render();
};

MRAGPP_NAMESPACE_END;

#endif
