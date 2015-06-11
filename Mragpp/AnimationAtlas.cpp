#include "StdH.h"
#include "AnimationAtlas.h"
#include "Renderer.h"
#include "Game.h"

using namespace Scratch;

MRAGPP_NAMESPACE_BEGIN;

CAnimationAtlasFrame::CAnimationAtlasFrame()
{
}

CAnimationAtlasFrame::~CAnimationAtlasFrame()
{
}

CAnimationAtlas::CAnimationAtlas()
{
}

CAnimationAtlas::~CAnimationAtlas()
{
}

void CAnimationAtlas::Load(CGame* pGame, const Filename &fnm)
{
  CAnimationAtlasFrame* pFrame = NULL;

	FileStream fs;
	fs.Open(fnm, "r");
	while(!fs.AtEOF()) {
		String strLine = fs.ReadLine();

		if(strLine == "") {
			continue;
		}

    if(atl_fnmTexture == "") {
			atl_fnmTexture = strLine;
			atl_texture.Load(pGame->Renderer, strLine);
			continue;
    }

    if(!strLine.Contains(':')) {
			pFrame = &atl_saFrames.Push();
			pFrame->anf_strName = strLine;
			pFrame->anf_iTime = 3;
			continue;
    }

		if(pFrame != NULL) {
			StackArray<String> aParse;
			strLine.Split(":", aParse);

			String strKey = aParse[0].Trim();
			String strValue = aParse[1].Trim();

			if(strKey == "rotate") {
				//TODO ?? usually is "false"?
			} else if(strKey == "xy") {
				pFrame->anf_vOffset = ParseVector2f(strValue);
			} else if(strKey == "size") {
				pFrame->anf_vSize = ParseVector2f(strValue);
			} else if(strKey == "orig") {
				//TODO ?? usually is same as size?
			} else if(strKey == "offset") {
				pFrame->anf_vOffset2 = ParseVector2f(strValue);
			} else if(strKey == "index") {
				//TODO ?? usually is "-1"?
			}
		}
	}
	fs.Close();
}

void CAnimationAtlas::AdvanceFrame()
{
	AdvanceFrame(atl_state);
}

void CAnimationAtlas::AdvanceFrame(CAnimationState &state)
{
	state.bPaused = false;
	state.iCurrentFrameCounter = 0;
	if(++state.iCurrentFrame >= atl_saFrames.Count()) {
		state.iCurrentFrame = 0;
	}
}

void CAnimationAtlas::Render(CRenderer &rend, const Vector2f &vPos)
{
	CAnimationAtlasFrame &frame = atl_saFrames[atl_state.iCurrentFrame];

	CRectangle rectDest;
	rectDest.x = vPos(1);
	rectDest.y = vPos(2);
	rectDest.w = frame.anf_vSize(1);
	rectDest.h = frame.anf_vSize(2);

	Render(rend, rectDest, atl_state);
}

void CAnimationAtlas::Render(CRenderer &rend, const Vector2f &vPos, float fRotation)
{
	CAnimationAtlasFrame &frame = atl_saFrames[atl_state.iCurrentFrame];

	CRectangle rectDest;
	rectDest.x = vPos(1);
	rectDest.y = vPos(2);
	rectDest.w = frame.anf_vSize(1);
	rectDest.h = frame.anf_vSize(2);
	rectDest.rotation = fRotation;

	Render(rend, rectDest, atl_state);
}

void CAnimationAtlas::Render(CRenderer &rend, const Vector2f &vPos, const Vector2f &vSize)
{
	CRectangle rectDest;
	rectDest.x = vPos(1);
	rectDest.y = vPos(2);
	rectDest.w = vSize(1);
	rectDest.h = vSize(2);

	Render(rend, rectDest, atl_state);
}

void CAnimationAtlas::Render(CRenderer &rend, const Vector2f &vPos, const Vector2f &vSize, float fRotation)
{
	CRectangle rectDest;
	rectDest.x = vPos(1);
	rectDest.y = vPos(2);
	rectDest.w = vSize(1);
	rectDest.h = vSize(2);
	rectDest.rotation = fRotation;

	Render(rend, rectDest, atl_state);
}

void CAnimationAtlas::Render(CRenderer &rend, const Vector2f &vPos, const Vector2f &vSize, float fRotation, CAnimationState &state)
{
	CRectangle rectDest;
	rectDest.x = vPos(1);
	rectDest.y = vPos(2);
	rectDest.w = vSize(1);
	rectDest.h = vSize(2);
	rectDest.rotation = fRotation;

	Render(rend, rectDest, state);
}

void CAnimationAtlas::Render(CRenderer &rend, const CRectangle &rect)
{
	Render(rend, rect, atl_state);
}

void CAnimationAtlas::Render(CRenderer &rend, const CRectangle &rect, CAnimationState &state)
{
	CAnimationAtlasFrame &frame = atl_saFrames[state.iCurrentFrame];

	CRectangle rectSource;
	rectSource.x = frame.anf_vOffset(1);
	rectSource.y = frame.anf_vOffset(2);
	rectSource.w = frame.anf_vSize(1);
	rectSource.h = frame.anf_vSize(2);

	rend.PutTexture(atl_texture, rect, rectSource, false, false);

	if(!state.bPaused && !frame.anf_bPause) {
		if(++state.iCurrentFrameCounter >= frame.anf_iTime) {
			AdvanceFrame(state);
		}
	}
}

MRAGPP_NAMESPACE_END;
