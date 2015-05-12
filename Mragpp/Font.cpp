#include "StdH.h"
#include "Font.h"

#ifdef _MSC_VER
#include <Windows.h>
#endif

#include <SDL_ttf.h>

MRAGPP_NAMESPACE_BEGIN;

CFont::CFont()
{
  fnt_pFont = 0;
}

CFont::CFont(TTF_Font* pFont)
{
  fnt_pFont = pFont;
}

CFont::~CFont()
{
  Destroy();
}

void CFont::Load(const char* szFilename, int iPtSize)
{
  if(fnt_pFont != 0) {
    Destroy();
  }

  fnt_pFont = TTF_OpenFont(szFilename, iPtSize);
  if(fnt_pFont == 0) {
    printf("SDL font loading error: '%s' while loading '%s'\n", TTF_GetError(), szFilename);
    return;
  }
}

void CFont::LoadFromPointer(unsigned char* pubBuffer, unsigned int iLen, int iPtSize)
{
  if(fnt_pFont != 0) {
    Destroy();
  }

  SDL_RWops* pRWops = SDL_RWFromMem((void*)pubBuffer, iLen);
  if(pRWops == 0) {
    printf("SDL RW ops error: '%s'\n", SDL_GetError());
    return;
  }

  fnt_pFont = TTF_OpenFontRW(pRWops, 1, iPtSize);
  if(fnt_pFont == 0) {
    printf("SDL font loading error: '%s' while loading from 0x%p\n", TTF_GetError(), pubBuffer);
    return;
  }
}

#ifdef _MSC_VER
void CFont::LoadFromResource(int iResID, int iPtSize)
{
  HMODULE hModule = GetModuleHandle("Mragpp");
  HRSRC hRes = FindResource(hModule, MAKEINTRESOURCE(iResID), MAKEINTRESOURCE(RT_FONT));
  if(hRes == 0) {
    int iLastError = GetLastError();
    printf("Last Windows error: %d\n", iLastError);
    return;
  }

  HGLOBAL hResBytes = LoadResource(hModule, hRes);
  unsigned char* pubBuffer = (UBYTE*)LockResource(hResBytes);
  LoadFromPointer(pubBuffer, SizeofResource(hModule, hRes), iPtSize);
  UnlockResource(hResBytes);
}
#endif

void CFont::Destroy()
{
  if(fnt_pFont == 0) {
    return;
  }

  TTF_CloseFont(fnt_pFont);
  fnt_pFont = 0;
}

CFont::operator TTF_Font*()
{
  return fnt_pFont;
}

MRAGPP_NAMESPACE_END;
