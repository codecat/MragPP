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
	Scratch::Dictionary<Scratch::String, CTexture> cnt_dicTextures;
	Scratch::Dictionary<Scratch::String, CFont> cnt_dicFonts;
	Scratch::Dictionary<Scratch::String, CAnimationSheet> cnt_dicAnimations;

public:
	CContentRegister();
	~CContentRegister();

	void Initialize(CGame* pGame);
	void Clear();

	CTexture &Texture(const Scratch::Filename &fnm);
	CFont &Font(const Scratch::Filename &fnm, int iPtSize);
	CAnimationSheet &Animation(const Scratch::Filename &fnm);
};

MRAGPP_NAMESPACE_END;

#endif
