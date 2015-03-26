#include "StdH.h"
#include "Texture.h"
#include "Renderer.h"

#ifdef _MSC_VER
#include <Windows.h>
#endif

#include <SDL.h>
#include <SDL_image.h>

MRAGPP_NAMESPACE_BEGIN;

CTexture::CTexture()
{
  tex_pRenderer = 0;
  tex_pTexture = 0;
  tex_iWidth = 0;
  tex_iHeight = 0;
  tex_iFormat = 0;
  tex_iAccess = 0;
  tex_bLoaded = false;
  tex_iLastAlpha = 0;
  tex_ebmLastBlendMode = BM_NONE;
  tex_colLast = COL_WHITE;
}

CTexture::CTexture(SDL_Texture* pTexture)
{
  tex_pRenderer = 0;
  tex_pTexture = pTexture;
  QueryTextureInfo();
}

CTexture::CTexture(CRenderer &renderer, const char* szFilename)
{
  tex_pRenderer = &renderer;
  tex_pTexture = 0;
  Load(renderer, szFilename);
}

CTexture::~CTexture()
{
  Destroy();
}

void CTexture::QueryTextureInfo()
{
  if(tex_pTexture == 0) {
    return;
  }

  SDL_QueryTexture(tex_pTexture, &tex_iFormat, &tex_iAccess, &tex_iWidth, &tex_iHeight);
  tex_bLoaded = true;
}

void CTexture::Load(CRenderer &renderer, const char* szFilename)
{
  if(tex_pTexture != 0) {
    Destroy();
  }

  tex_pRenderer = &renderer;
  tex_pTexture = IMG_LoadTexture(renderer, szFilename);
  if(tex_pTexture == 0) {
    printf("SDL texture loading error: '%s' while loading '%s'\n", IMG_GetError(), szFilename);
    return;
  }

  QueryTextureInfo();
}

void CTexture::LoadFromPointer(CRenderer &renderer, unsigned char* pubBuffer, unsigned int iLen)
{
  if(tex_pTexture != 0) {
    Destroy();
  }

  tex_pRenderer = &renderer;
  tex_pTexture = IMG_LoadTexture_RW(renderer, SDL_RWFromMem((void*)pubBuffer, iLen), 1);
  if(tex_pTexture == 0) {
    printf("SDL texture loading error: '%s' while loading from memory\n", IMG_GetError());
    return;
  }

  QueryTextureInfo();
}

#ifdef _MSC_VER
void CTexture::LoadFromResource(CRenderer &renderer, int iResID)
{
  HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(iResID), "Font");
  HGLOBAL hResBytes = LoadResource(NULL, hRes);
  unsigned char* pubBuffer = (UBYTE*)LockResource(hResBytes);
  LoadFromPointer(renderer, pubBuffer, SizeofResource(NULL, hRes));
}
#endif

void CTexture::SetAlphaMod(COLOR_VALUE alpha)
{
  if(tex_pTexture == 0) {
    return;
  }

  if(alpha == tex_iLastAlpha) {
    return;
  }

  tex_iLastAlpha = alpha;

  SDL_SetTextureAlphaMod(tex_pTexture, alpha);
}

void CTexture::SetBlendingMode(ETextureBlendMode ebm)
{
  if(tex_pTexture == 0) {
    return;
  }

  if(ebm == tex_ebmLastBlendMode) {
    return;
  }

  tex_ebmLastBlendMode = ebm;

  SDL_BlendMode bm = SDL_BLENDMODE_NONE;
  switch(ebm) {
  case BM_BLEND: bm = SDL_BLENDMODE_BLEND; break;
  case BM_ADD: bm = SDL_BLENDMODE_ADD; break;
  case BM_MOD: bm = SDL_BLENDMODE_MOD; break;
  default: break;
  }

  SDL_SetTextureBlendMode(tex_pTexture, bm);
}

void CTexture::SetColorMod(COLOR col)
{
  if(tex_pTexture == 0) {
    return;
  }

  if(col == tex_colLast) {
    return;
  }

  tex_colLast = col;

  COLOR_VALUE r, g, b;
  MRAG_COLOR_EXPLODE_RGB(col, r, g, b);

  SDL_SetTextureColorMod(tex_pTexture, r, g, b);
}

void CTexture::Destroy()
{
  if(tex_pTexture == 0) {
    return;
  }

  SDL_DestroyTexture(tex_pTexture);
  tex_pTexture = 0;
}

CTexture::operator SDL_Texture*()
{
  return tex_pTexture;
}

MRAGPP_NAMESPACE_END;
