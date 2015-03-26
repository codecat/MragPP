#include "StdH.h"
#include "Paths.h"

MRAGPP_NAMESPACE_BEGIN;

CPaths::CPaths()
{
  ps_iIterator = 0;
}

CPaths::~CPaths()
{
  ps_aPaths.Clear();
}

CPath& CPaths::Create(const Vector2f &vPos1, const Vector2f &vPos2, int iTotalFrameCount,
  mragPathsOnUpdateFunction onUpdate, mragPathsOnFinishFunction onFinish)
{
  CPath &newPath = ps_aPaths.Push();
  newPath.p_pPaths = this;
  newPath.p_vPos1 = vPos1;
  newPath.p_vPos2 = vPos2;
  newPath.p_iTotalFrameCount = iTotalFrameCount;
  newPath.p_pOnUpdate = onUpdate;
  newPath.p_pOnFinish = onFinish;
  return newPath;
}

CPath& CPaths::Create(const Vector2f &vPos1, const Vector2f &vPos2, float fSeconds,
  mragPathsOnUpdateFunction onUpdate, mragPathsOnFinishFunction onFinish)
{
  return Create(vPos1, vPos2, (int)ceil(fSeconds / 0.0166667f), onUpdate, onFinish);
}

void CPaths::Update()
{
  for(int i=0; i<ps_aPaths.Count(); i++) {
    ps_aPaths[i].p_bReady = true;
  }

  for(ps_iIterator=0; ps_iIterator<ps_aPaths.Count(); ps_iIterator++) {
    if(!ps_aPaths[ps_iIterator].p_bReady) {
      continue;
    }
    ps_aPaths[ps_iIterator].Update();
  }
}

void CPaths::Render()
{
  for(ps_iIterator=0; ps_iIterator<ps_aPaths.Count(); ps_iIterator++) {
    ps_aPaths[ps_iIterator].Render();
  }
}

MRAGPP_NAMESPACE_END;
