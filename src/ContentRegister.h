#ifndef MRAGPP_CONTENTREGISTER_H_INCLUDED
#define MRAGPP_CONTENTREGISTER_H_INCLUDED

#include "StdH.h"
#include "Texture.h"
#include "Font.h"
#include "AnimationSheet.h"

MRAGPP_NAMESPACE_BEGIN;

class MRAGPP_EXPORT CGame;

class MRAGPP_EXPORT CContentRegister
{
public:
	CGame* cnt_pGame;
	Scratch::CDictionary<Scratch::CString, CTexture> cnt_dicTextures;
	Scratch::CDictionary<Scratch::CString, CFont> cnt_dicFonts;
	Scratch::CDictionary<Scratch::CString, CAnimationSheet> cnt_dicAnimations;

public:
	CContentRegister();
	~CContentRegister();

	void Initialize(CGame* pGame);

	CTexture &Texture(const Scratch::CFilename &fnm);
	CFont &Font(const Scratch::CFilename &fnm, int iPtSize);
	CAnimationSheet &Animation(const Scratch::CFilename &fnm);
};

MRAGPP_NAMESPACE_END;

#endif
