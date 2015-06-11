#ifndef MRAGPP_ANIMATIONSHEET_H_INCLUDED
#define MRAGPP_ANIMATIONSHEET_H_INCLUDED

#include "StdH.h"
#include "Texture.h"
#include "Rectangle.h"
#include "Xml/XmlFile.h"

MRAGPP_NAMESPACE_BEGIN;

class CAnimation;
class CAnimationSheet;

/* instantiate this class and pass it on the animation rendering functions
   to use a custom state instead of the animation sheet object's internal
   state. this is not required by any means, but makes it possible to use
   a single animation sheet object for multiple entities, for example */
class MRAGPP_EXPORT CAnimationState
{
public:
  int iCurrentFrame;
  int iCurrentFrameCounter;
  bool bPaused;

public:
  CAnimationState();
  ~CAnimationState();

  void Reset();
};

class MRAGPP_EXPORT CAnimationFrame
{
  friend class CAnimation;
public:
  Vector2f anf_vOffset;
  int anf_iTime;
  bool anf_bPause;

public:
  CAnimationFrame();
  virtual ~CAnimationFrame();

private:
  virtual void Load(XmlTag &tagFrame);
};

class MRAGPP_EXPORT CAnimation
{
  friend class CAnimationSheet;
public:
  CAnimationSheet* ani_pSheet;

  Scratch::StackArray<CAnimationFrame> ani_saFrames;
  Scratch::String ani_strName;

  Vector2f ani_vSize;
  CRectangle ani_rectOffset;

  bool ani_bResetOnActive;
  bool ani_bLooping;
  int ani_iStartFrame;
  int ani_iLoopFrame;

  CAnimation* ani_pAliasOwner;
  bool ani_bFlipH;
  bool ani_bFlipV;

  COLOR_VALUE ani_iAlphaMultiplier;
  ETextureBlendMode ani_ebmBlendMode;
  COLOR ani_colMultiplier;

  CAnimationState ani_state;

public:
  CAnimation();
  ~CAnimation();

  Vector2i Render(const Vector2f &vPos, CAnimationState &state, float fRotation = 0.0f, float fOverX = 0.0f, float fOverY = 0.0f);
  Vector2i Render(const Vector2f &vPos, const Vector2f &vSize, CAnimationState &state, float fRotation = 0.0f, float fOverX = 0.0f, float fOverY = 0.0f);

private:
  void SetActive(CAnimationState &state);
  void AdvanceFrame(); // this will also unpause the animation state
  void AdvanceFrame(CAnimationState &state); // this will also unpause the animation state

  void Load(XmlTag &tagAnim);
};

class CGame;

class MRAGPP_EXPORT CAnimationSheet
{
public:
  Scratch::StackArray<CAnimation> ans_saAnimations;
  Scratch::String ans_strName;
  Scratch::String ans_strTextureFilename;
  CTexture* ans_pTexture;
  Scratch::Dictionary<int, CTexture> ans_saHues;
  XmlFile* ans_pXml;
  CRenderer* ans_pRenderer;
  BOOL ans_bCenter;
  BOOL ans_bLoaded;

  Scratch::String ans_strLatestAnimation;

public:
  CAnimationSheet();
  CAnimationSheet(CGame* pGame, const Scratch::String &strFilename);
  ~CAnimationSheet();

  CAnimation* GetAnimation(const Scratch::String &strName);

  void Load(CGame* pGame, const Scratch::String &strFilename);
  void Unload();

  void SetAlphaMult(const Scratch::String &strAnimationName, COLOR_VALUE iAlpha);
  void SetBlendingMode(const Scratch::String &strAnimationName, ETextureBlendMode ebm);
  void SetColorMult(const Scratch::String &strAnimationName, COLOR colMult);

  Vector2i Render(const Scratch::String &strName, const Vector2f &vPos, float fRotation = 0.0f, float fOverX = 0.0f, float fOverY = 0.0f);
  Vector2i Render(const Scratch::String &strName, const Vector2f &vPos, CAnimationState &state, float fRotation = 0.0f, float fOverX = 0.0f, float fOverY = 0.0f);
  Vector2i Render(const Scratch::String &strName, const Vector2f &vPos, const Vector2f &vSize, float fRotation = 0.0f, float fOverX = 0.0f, float fOverY = 0.0f);
  Vector2i Render(const Scratch::String &strName, const Vector2f &vPos, const Vector2f &vSize, CAnimationState &state, float fRotation = 0.0f, float fOverX = 0.0f, float fOverY = 0.0f);
};

class MRAGPP_EXPORT CAnimationSheetCollection
{
public:
  Scratch::StackArray<CAnimationSheet> asc_saSheets;
  XmlFile* asc_pXml;

public:
  CAnimationSheetCollection();
  ~CAnimationSheetCollection();

  void Load(CGame* pGame, const Scratch::String &strFilename);
  void Unload();

  void Add(CGame* pGame, const Scratch::String &strFilename);
  CAnimationSheet* GetSheet(const Scratch::String &strName);

  void SetAlphaMult(const Scratch::String &strSheetName, const Scratch::String &strAnimationName, COLOR_VALUE iAlpha);
  void SetBlendingMode(const Scratch::String &strSheetName, const Scratch::String &strAnimationName, ETextureBlendMode ebm);
  void SetColorMult(const Scratch::String &strSheetName, const Scratch::String &strAnimationName, COLOR colMult);

  Vector2i Render(const Scratch::String &strSheetName, const Scratch::String &strAnimationName, const Vector2f &vPos, float fRotation = 0.0f, float fOverX = 0.0f, float fOverY = 0.0f);
  Vector2i Render(const Scratch::String &strSheetName, const Scratch::String &strAnimationName, const Vector2f &vPos, CAnimationState &state, float fRotation = 0.0f, float fOverX = 0.0f, float fOverY = 0.0f);
  Vector2i Render(const Scratch::String &strSheetName, const Scratch::String &strAnimationName, const Vector2f &vPos, const Vector2f &vSize, float fRotation = 0.0f, float fOverX = 0.0f, float fOverY = 0.0f);
  Vector2i Render(const Scratch::String &strSheetName, const Scratch::String &strAnimationName, const Vector2f &vPos, const Vector2f &vSize, CAnimationState &state, float fRotation = 0.0f, float fOverX = 0.0f, float fOverY = 0.0f);

  Vector2i GetSize(const Scratch::String &strSheetName, const Scratch::String &strAnimationName);

  CAnimationSheet &operator[](const Scratch::String &strName);
};

MRAGPP_NAMESPACE_END;

#endif
