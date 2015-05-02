#ifndef MRAGPP_ANIMATIONJSON_H_INCLUDED
#define MRAGPP_ANIMATIONJSON_H_INCLUDED

#include "StdH.h"
#include "Texture.h"
#include "Rectangle.h"

#include "spine/spine.h"
#include "spine/extension.h"

MRAGPP_NAMESPACE_BEGIN;

class CGame;

/**
 * This class is for handling animations exported by Spine into the
 * json format. This allows for complex animations, as well as merging
 * from one animation to the other.
 */
class MRAGPP_EXPORT CAnimationJson
{
private:
	spSkeleton* ani_pSkeleton;
	spSkeletonData* ani_pSkeletonData;
	spAnimationState* ani_pState;
	float* ani_pWorldVertices;

public:
	CAnimationJson();
	~CAnimationJson();

	void Load(CGame* pGame, const char* szAtlas, const char* szJson);
	/**
	 * Dump some info about the loaded data to stdout. Useful for debugging.
	 */
	void DumpInfo();

	void SetAnimation(const char* szName, bool bLooping);

	void Update(float fDeltatime);

	void Render(CRenderer &rend, const Vector2f &vPos);
	void Render(CRenderer &rend, const Vector2f &vPos, float fRotation);
	void Render(CRenderer &rend, const Vector2f &vPos, const Vector2f &vScale);
	void Render(CRenderer &rend, const Vector2f &vPos, const Vector2f &vScale, float fRotation);
};

MRAGPP_NAMESPACE_END;

#endif
