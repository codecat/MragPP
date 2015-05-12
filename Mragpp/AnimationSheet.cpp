#include "StdH.h"
#include "AnimationSheet.h"
#include "Renderer.h"
#include "Game.h"

using namespace Scratch;

MRAGPP_NAMESPACE_BEGIN;

/************************************
 * Animation State
 ************************************/
CAnimationState::CAnimationState()
{
  Reset();
}

CAnimationState::~CAnimationState()
{
}

void CAnimationState::Reset()
{
  iCurrentFrame = 0;
  iCurrentFrameCounter = 0;
  bPaused = false;
}

/************************************
 * Animation Frame <frame>
 ************************************/
CAnimationFrame::CAnimationFrame()
{
  anf_iTime = 1;
  anf_bPause = false;
}

CAnimationFrame::~CAnimationFrame()
{
}

void CAnimationFrame::Load(XmlTag &tagFrame)
{
  if(tagFrame.Attributes.HasKey("offset")) { anf_vOffset = ParseVector2f(tagFrame.Attributes["offset"]); }
  if(tagFrame.Attributes.HasKey("time"))   { anf_iTime   = atoi(tagFrame.Attributes["time"]); }
  if(tagFrame.Attributes.HasKey("pause"))  { anf_bPause  = ParseBool(tagFrame.Attributes["pause"]); }
}

/************************************
 * Animation <anim>
 ************************************/
CAnimation::CAnimation()
{
  ani_bResetOnActive = false;
  ani_bLooping = true;
  ani_iStartFrame = 0;
  ani_iLoopFrame = 0;

  ani_pAliasOwner = 0;
  ani_bFlipH = false;
  ani_bFlipV = false;

  ani_iAlphaMultiplier = 255;
  ani_ebmBlendMode = BM_NONE;
  ani_colMultiplier = COL_WHITE;
}

CAnimation::~CAnimation()
{
}

void CAnimation::SetActive(CAnimationState &state)
{
  CAnimation* pAnim = this;
  if(ani_pAliasOwner != 0) {
    pAnim = ani_pAliasOwner;
  }

  if(pAnim->ani_bResetOnActive) {
    ani_state.iCurrentFrame = ani_iStartFrame;
    ani_state.iCurrentFrameCounter = 0;
  }
}

void CAnimation::AdvanceFrame()
{
  AdvanceFrame(ani_state);
}

void CAnimation::AdvanceFrame(CAnimationState &state)
{
  CAnimation* pAnim = this;
  if(ani_pAliasOwner != 0) {
    pAnim = ani_pAliasOwner;
  }

  state.bPaused = false;
  state.iCurrentFrameCounter = 0;
  if(++state.iCurrentFrame >= pAnim->ani_saFrames.Count()) {
    state.iCurrentFrame = pAnim->ani_iLoopFrame;
  }
}

void CAnimation::Load(XmlTag &tagAnim)
{
  if(tagAnim.Attributes.HasKey("name"))          { ani_strName        = tagAnim.Attributes["name"]; }
  if(tagAnim.Attributes.HasKey("size"))          { ani_vSize          = ParseVector2f(tagAnim.Attributes["size"]); }
  if(tagAnim.Attributes.HasKey("offset"))        { ani_rectOffset     = ParseRectangle(tagAnim.Attributes["offset"]); }
  if(tagAnim.Attributes.HasKey("resetonactive")) { ani_bResetOnActive = ParseBool(tagAnim.Attributes["resetonactive"]); }
  if(tagAnim.Attributes.HasKey("looping"))       { ani_bLooping       = ParseBool(tagAnim.Attributes["looping"]); }
  if(tagAnim.Attributes.HasKey("startframe"))    { ani_iStartFrame    = atoi(tagAnim.Attributes["startframe"]); }
  if(tagAnim.Attributes.HasKey("loopframe"))     { ani_iLoopFrame     = atoi(tagAnim.Attributes["loopframe"]); }
  if(tagAnim.Attributes.HasKey("fliph"))         { ani_bFlipH         = ParseBool(tagAnim.Attributes["fliph"]); }
  if(tagAnim.Attributes.HasKey("flipv"))         { ani_bFlipV         = ParseBool(tagAnim.Attributes["flipv"]); }

  ani_state.iCurrentFrame = ani_iStartFrame;

  CStackArray<XmlTag> xmlFrames;
  tagAnim.FindChildrenByName("frame", xmlFrames);

  for(int i=0; i<xmlFrames.Count(); i++) {
    XmlTag &tag = xmlFrames[i];
    CAnimationFrame &frame = ani_saFrames.Push();
    frame.Load(tag);
  }

  CStackArray<XmlTag> xmlAliases;
  tagAnim.FindChildrenByName("alias", xmlAliases);

  for(int i=0; i<xmlAliases.Count(); i++) {
    XmlTag &tag = xmlAliases[i];
    CAnimation &anim = ani_pSheet->ans_saAnimations.Push();
    anim.ani_strName = tag.Attributes["name"];
    anim.ani_pAliasOwner = this;
    if(tag.Attributes.HasKey("fliph")) { anim.ani_bFlipH = ParseBool(tag.Attributes["fliph"]); }
    if(tag.Attributes.HasKey("flipv")) { anim.ani_bFlipV = ParseBool(tag.Attributes["flipv"]); }
    //if(tag.Attributes.HasKey("hue"))   { anim.ani_iHue   = atoi(tag.Attributes["hue"]); } //TODO: Replace this with color multiplier
  }
}

Vector2i CAnimation::Render(const Vector2f &vPos, CAnimationState &state, float fRotation, float fOverX, float fOverY)
{
  CAnimation* pAnim = this;
  if(ani_pAliasOwner != 0) {
    pAnim = ani_pAliasOwner;
  }

  return Render(vPos, pAnim->ani_vSize, state, fRotation, fOverX, fOverY);
}

Vector2i CAnimation::Render(const Vector2f &vPos, const Vector2f &vSize, CAnimationState &state, float fRotation, float fOverX, float fOverY)
{
  CAnimation* pAnim = this;
  if(ani_pAliasOwner != 0) {
    pAnim = ani_pAliasOwner;
  }

  pAnim->ani_pSheet->ans_pTexture->SetAlphaMod(ani_iAlphaMultiplier);
  pAnim->ani_pSheet->ans_pTexture->SetBlendingMode(ani_ebmBlendMode);
  pAnim->ani_pSheet->ans_pTexture->SetColorMod(ani_colMultiplier);

  CRenderer &rend = *pAnim->ani_pSheet->ans_pRenderer;
  CTexture &tex = *pAnim->ani_pSheet->ans_pTexture;

  if(state.iCurrentFrame >= pAnim->ani_saFrames.Count()) {
    // this can happen if different animations are used on the same state
    state.Reset();
  }
  CAnimationFrame &frame = pAnim->ani_saFrames[state.iCurrentFrame];

  CRectangle rectDest;
  rectDest.w = vSize(1);
  rectDest.h = vSize(2);

  float fOffsetX = pAnim->ani_rectOffset.x;
  float fOffsetY = pAnim->ani_rectOffset.y;

  float fWidth = pAnim->ani_rectOffset.w;
  if(fWidth == 0) { fWidth = vSize(1); }
  if(ani_bFlipH) { fOffsetX -= ((fOffsetX - rectDest.w / 2) * 2) + fWidth; }

  float fHeight = pAnim->ani_rectOffset.h;
  if(fHeight == 0) { fHeight = vSize(2); }
  if(ani_bFlipV) { fOffsetY -= ((fOffsetY - rectDest.h / 2) * 2) + fHeight; }

  rectDest.x = vPos(1) - fOffsetX;
  rectDest.y = vPos(2) - fOffsetY;
  rectDest.rotation = fRotation;

  CRectangle rectSrc;
  rectSrc.x = frame.anf_vOffset(1);
  rectSrc.y = frame.anf_vOffset(2);
  rectSrc.w = pAnim->ani_vSize(1);
  rectSrc.h = pAnim->ani_vSize(2);

  if(fOverX > 0) { rectDest.w = fOverX; }
  if(fOverY > 0) { rectDest.h = fOverY; }

  rectDest.anchorInCenter = pAnim->ani_pSheet->ans_bCenter ? true : false;
  rend.PutTexture(tex, rectDest, rectSrc, ani_bFlipH, ani_bFlipV);

  if(!frame.anf_bPause) {
    if(++state.iCurrentFrameCounter >= frame.anf_iTime) {
      AdvanceFrame(state);
    }
  }

  // hmm..
  if(fOverX > 0) { fWidth = fOverX; }
  if(fOverY > 0) { fHeight = fOverY; }

  return Vector2i((int)fWidth, (int)fHeight);
}

/************************************
 * Animation Sheet <sheet>
 ************************************/
CAnimationSheet::CAnimationSheet()
{
  ans_pTexture = 0;
  ans_pXml = 0;
  ans_pRenderer = 0;
  ans_bCenter = FALSE;
  ans_bLoaded = FALSE;
}

CAnimationSheet::CAnimationSheet(CGame* pGame, const CString &strFilename)
{
  Load(pGame, strFilename);
  ans_bCenter = FALSE;
}

CAnimationSheet::~CAnimationSheet()
{
  Unload();
}

CAnimation* CAnimationSheet::GetAnimation(const Scratch::CString &strName)
{
  for(int i=0; i<ans_saAnimations.Count(); i++) {
    CAnimation &anim = ans_saAnimations[i];
    if(anim.ani_strName == strName) {
      return &anim;
    }
  }
  return 0;
}

void CAnimationSheet::Load(CGame* pGame, const CString &strFilename)
{
  ans_pRenderer = &pGame->Renderer;

  ASSERT(ans_pTexture == 0 && ans_pXml == 0);
  ans_strTextureFilename = strFilename;
  ans_pTexture = &(pGame->Content.Texture(strFilename));
  ans_pXml = new XmlFile(strFilename.Replace(".png", ".xml"));

  XmlTag* xmlSheet = ans_pXml->Root->FindChildByName("sheet");

  if(xmlSheet->Attributes.HasKey("name")) { ans_strName = xmlSheet->Attributes["name"]; }

  CStackArray<XmlTag> xmlAnimations;
  xmlSheet->FindChildrenByName("anim", xmlAnimations);

  for(int i=0; i<xmlAnimations.Count(); i++) {
    XmlTag &tag = xmlAnimations[i];
    CAnimation &anim = ans_saAnimations.Push();
    anim.ani_pSheet = this;
    anim.Load(tag);
  }

  ans_bLoaded = TRUE;
}

void CAnimationSheet::Unload()
{
  //NOTE: Don't delete texture here because this comes from the game's content register!
  ans_pTexture = 0;
  if(ans_pXml != 0) {
    delete ans_pXml;
    ans_pXml = 0;
  }
  ans_saHues.Clear();
  ans_bLoaded = FALSE;
}

void CAnimationSheet::SetAlphaMult(const Scratch::CString &strAnimationName, COLOR_VALUE iAlpha)
{
  CAnimation* pAnim = GetAnimation(strAnimationName);
  ASSERT(pAnim != 0);
  if(pAnim == 0) {
    return;
  }

  pAnim->ani_iAlphaMultiplier = iAlpha;
}

void CAnimationSheet::SetBlendingMode(const Scratch::CString &strAnimationName, ETextureBlendMode ebm)
{
  CAnimation* pAnim = GetAnimation(strAnimationName);
  ASSERT(pAnim != 0);
  if(pAnim == 0) {
    return;
  }

  pAnim->ani_ebmBlendMode = ebm;
}

void CAnimationSheet::SetColorMult(const Scratch::CString &strAnimationName, COLOR colMult)
{
  CAnimation* pAnim = GetAnimation(strAnimationName);
  ASSERT(pAnim != 0);
  if(pAnim == 0) {
    return;
  }

  pAnim->ani_colMultiplier = colMult;
}

Vector2i CAnimationSheet::Render(const CString &strName, const Vector2f &vPos, float fRotation, float fOverX, float fOverY)
{
  CAnimation* pAnim = GetAnimation(strName);
  ASSERT(pAnim != 0);
  if(pAnim == 0) {
    return Vector2i(0, 0);
  }

  if(ans_strLatestAnimation != strName) {
    ans_strLatestAnimation = strName;
    pAnim->SetActive(pAnim->ani_state);
  }

  return pAnim->Render(vPos, pAnim->ani_state, fRotation, fOverX, fOverY);
}

Vector2i CAnimationSheet::Render(const Scratch::CString &strName, const Vector2f &vPos, CAnimationState &state, float fRotation, float fOverX, float fOverY)
{
  CAnimation* pAnim = GetAnimation(strName);
  ASSERT(pAnim != 0);
  if(pAnim == 0) {
    return Vector2i(0, 0);
  }

  if(ans_strLatestAnimation != strName) {
    ans_strLatestAnimation = strName;
    pAnim->SetActive(state);
  }

  return pAnim->Render(vPos, state, fRotation, fOverX, fOverY);
}

Vector2i CAnimationSheet::Render(const Scratch::CString &strName, const Vector2f &vPos, const Vector2f &vSize, float fRotation, float fOverX, float fOverY)
{
  CAnimation* pAnim = GetAnimation(strName);
  ASSERT(pAnim != 0);
  if(pAnim == 0) {
    return Vector2i(0, 0);
  }

  if(ans_strLatestAnimation != strName) {
    ans_strLatestAnimation = strName;
    pAnim->SetActive(pAnim->ani_state);
  }

  return pAnim->Render(vPos, vSize, pAnim->ani_state, fRotation, fOverX, fOverY);
}

Vector2i CAnimationSheet::Render(const Scratch::CString &strName, const Vector2f &vPos, const Vector2f &vSize, CAnimationState &state, float fRotation, float fOverX, float fOverY)
{
  CAnimation* pAnim = GetAnimation(strName);
  ASSERT(pAnim != 0);
  if(pAnim == 0) {
    return Vector2i(0, 0);
  }

  if(ans_strLatestAnimation != strName) {
    ans_strLatestAnimation = strName;
    pAnim->SetActive(state);
  }

  return pAnim->Render(vPos, vSize, state, fRotation, fOverX, fOverY);
}

/************************************
 * Animation Sheet Collection <sheets>
 ************************************/
CAnimationSheetCollection::CAnimationSheetCollection()
{
  asc_pXml = 0;
}

CAnimationSheetCollection::~CAnimationSheetCollection()
{
  Unload();
}

void CAnimationSheetCollection::Load(CGame* pGame, const CString &strFilename)
{
  Unload();

  asc_pXml = new XmlFile(strFilename);
  XmlTag* pSheets = asc_pXml->Root->FindChildByName("sheets");
  ASSERT(pSheets != 0);
  if(pSheets == 0) {
    return;
  }

  CStackArray<XmlTag> sheets;
  pSheets->FindChildrenByName("sheet", sheets);

  for(int i=0; i<sheets.Count(); i++) {
    Add(pGame, sheets[i].Value);
  }
}

void CAnimationSheetCollection::Unload()
{
  if(asc_pXml != 0) {
    delete asc_pXml;
    asc_pXml = 0;
  }
}

void CAnimationSheetCollection::Add(CGame* pGame, const CString &strFilename)
{
  CAnimationSheet &sheet = asc_saSheets.Push();
  sheet.Load(pGame, strFilename);
}

CAnimationSheet* CAnimationSheetCollection::GetSheet(const CString &strName)
{
  for(int i=0; i<asc_saSheets.Count(); i++) {
    if(asc_saSheets[i].ans_strName == strName) {
      return &asc_saSheets[i];
    }
  }
  return 0;
}

void CAnimationSheetCollection::SetAlphaMult(const Scratch::CString &strSheetName, const Scratch::CString &strAnimationName, COLOR_VALUE iAlpha)
{
  CAnimationSheet* pSheet = GetSheet(strSheetName);
  ASSERT(pSheet != 0);
  if(pSheet == 0) {
    return;
  }

  pSheet->SetAlphaMult(strAnimationName, iAlpha);
}

void CAnimationSheetCollection::SetBlendingMode(const Scratch::CString &strSheetName, const Scratch::CString &strAnimationName, ETextureBlendMode ebm)
{
  CAnimationSheet* pSheet = GetSheet(strSheetName);
  ASSERT(pSheet != 0);
  if(pSheet == 0) {
    return;
  }

  pSheet->SetBlendingMode(strAnimationName, ebm);
}

void CAnimationSheetCollection::SetColorMult(const Scratch::CString &strSheetName, const Scratch::CString &strAnimationName, COLOR colMult)
{
  CAnimationSheet* pSheet = GetSheet(strSheetName);
  ASSERT(pSheet != 0);
  if(pSheet == 0) {
    return;
  }

  pSheet->SetColorMult(strAnimationName, colMult);
}

Vector2i CAnimationSheetCollection::Render(const CString &strSheetName, const CString &strAnimationName, const Vector2f &vPos, float fRotation, float fOverX, float fOverY)
{
  CAnimationSheet* pSheet = GetSheet(strSheetName);
  ASSERT(pSheet != 0);
  if(pSheet == 0) {
    return Vector2i(0, 0);
  }

  return pSheet->Render(strAnimationName, vPos, fRotation, fOverX, fOverY);
}

Vector2i CAnimationSheetCollection::Render(const CString &strSheetName, const CString &strAnimationName, const Vector2f &vPos, CAnimationState &state, float fRotation, float fOverX, float fOverY)
{
  CAnimationSheet* pSheet = GetSheet(strSheetName);
  ASSERT(pSheet != 0);
  if(pSheet == 0) {
    return Vector2i(0, 0);
  }

  return pSheet->Render(strAnimationName, vPos, state, fRotation, fOverX, fOverY);
}

Vector2i CAnimationSheetCollection::Render(const Scratch::CString &strSheetName, const Scratch::CString &strAnimationName, const Vector2f &vPos, const Vector2f &vSize, float fRotation, float fOverX, float fOverY)
{
  CAnimationSheet* pSheet = GetSheet(strSheetName);
  ASSERT(pSheet != 0);
  if(pSheet == 0) {
    return Vector2i(0, 0);
  }

  return pSheet->Render(strAnimationName, vPos, vSize, fRotation, fOverX, fOverY);
}

Vector2i CAnimationSheetCollection::Render(const Scratch::CString &strSheetName, const Scratch::CString &strAnimationName, const Vector2f &vPos, const Vector2f &vSize, CAnimationState &state, float fRotation, float fOverX, float fOverY)
{
  CAnimationSheet* pSheet = GetSheet(strSheetName);
  ASSERT(pSheet != 0);
  if(pSheet == 0) {
    return Vector2i(0, 0);
  }

  return pSheet->Render(strAnimationName, vPos, vSize, state, fRotation, fOverX, fOverY);
}

Vector2i CAnimationSheetCollection::GetSize(const Scratch::CString &strSheetName, const Scratch::CString &strAnimationName)
{
  CAnimationSheet* pSheet = GetSheet(strSheetName);
  ASSERT(pSheet != 0);
  if(pSheet == 0) {
    return Vector2i(0, 0);
  }

  CAnimation* pAnim = pSheet->GetAnimation(strAnimationName);
  ASSERT(pAnim != 0);
  if(pAnim == 0) {
    return Vector2i(0, 0);
  }

  return pAnim->ani_vSize.GetAs<2,int>();
}

CAnimationSheet &CAnimationSheetCollection::operator[](const CString &strName)
{
  return *GetSheet(strName);
}

MRAGPP_NAMESPACE_END;
