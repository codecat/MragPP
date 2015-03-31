#include "StdH.h"
#include "ContentRegister.h"
#include "Game.h"

using namespace Scratch;

MRAGPP_NAMESPACE_BEGIN;

CContentRegister::CContentRegister()
{
	cnt_pGame = 0;
}

CContentRegister::~CContentRegister()
{
}

void CContentRegister::Initialize(CGame* pGame)
{
	cnt_pGame = pGame;
}

void CContentRegister::Clear()
{
	cnt_dicTextures.Clear();
	cnt_dicFonts.Clear();
	cnt_dicAnimations.Clear();
}

CTexture &CContentRegister::Texture(const Scratch::CFilename &fnm)
{
	if(cnt_dicTextures.HasKey(fnm)) {
		return cnt_dicTextures[fnm];
	}
	CDictionaryPair<CString, CTexture> pair = cnt_dicTextures.Push(fnm);
	CTexture &tex = *pair.value;
	tex.Load(cnt_pGame->Renderer, fnm);
	return tex;
}

CFont &CContentRegister::Font(const Scratch::CFilename &fnm, int iPtSize)
{
	if(cnt_dicFonts.HasKey(fnm)) {
		return cnt_dicFonts[fnm];
	}
	CDictionaryPair<CString, CFont> pair = cnt_dicFonts.Push(fnm);
	CFont &font = *pair.value;
	font.Load(fnm, iPtSize);
	return font;
}

CAnimationSheet &CContentRegister::Animation(const Scratch::CFilename &fnm)
{
	if(cnt_dicAnimations.HasKey(fnm)) {
		return cnt_dicAnimations[fnm];
	}
	CDictionaryPair<CString, CAnimationSheet> pair = cnt_dicAnimations.Push(fnm);
	CAnimationSheet &sheet = *pair.value;
	sheet.Load(cnt_pGame, fnm);
	return sheet;
}

MRAGPP_NAMESPACE_END;
