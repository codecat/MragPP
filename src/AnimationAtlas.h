#ifndef MRAGPP_ANIMATIONATLAS_H_INCLUDED
#define MRAGPP_ANIMATIONATLAS_H_INCLUDED

#include "StdH.h"
#include "Texture.h"
#include "Rectangle.h"
#include "AnimationSheet.h"

MRAGPP_NAMESPACE_BEGIN;

class MRAGPP_EXPORT CAnimationAtlasFrame : public CAnimationFrame
{
public:
	Scratch::CString anf_strName;
	Vector2f anf_vSize;
	Vector2f anf_vOffset2;

public:
	CAnimationAtlasFrame();
	virtual ~CAnimationAtlasFrame();
};

class CGame;

/**
 * This class is for parsing and rendering atlas animations created by
 * programs such as Spine.
 */
class MRAGPP_EXPORT CAnimationAtlas
{
public:
	CTexture atl_texture;
	Scratch::CFilename atl_fnmTexture;

	CAnimationState atl_state;

	Scratch::CStackArray<CAnimationAtlasFrame> atl_saFrames;

public:
	CAnimationAtlas();
	~CAnimationAtlas();

	void Load(CGame* pGame, const Scratch::CFilename &fnm);

	void AdvanceFrame(); // this will also unpause the animation state
	void AdvanceFrame(CAnimationState &state); // this will also unpause the animation state

	void Render(CRenderer &rend, const Vector2f &vPos);
	void Render(CRenderer &rend, const Vector2f &vPos, float fRotation);
	void Render(CRenderer &rend, const Vector2f &vPos, const Vector2f &vSize);
	void Render(CRenderer &rend, const Vector2f &vPos, const Vector2f &vSize, float fRotation);
	void Render(CRenderer &rend, const Vector2f &vPos, const Vector2f &vSize, float fRotation, CAnimationState &state);
	void Render(CRenderer &rend, const CRectangle &rect);
	void Render(CRenderer &rend, const CRectangle &rect, CAnimationState &state);
};

MRAGPP_NAMESPACE_END;

#endif
