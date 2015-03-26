#ifndef MRAGPP_TEXTURE_H_INCLUDED
#define MRAGPP_TEXTURE_H_INCLUDED

#include "StdH.h"

struct SDL_Texture;

MRAGPP_NAMESPACE_BEGIN;

enum MRAGPP_EXPORT ETextureBlendMode
{
  BM_NONE,
  BM_BLEND,
  BM_ADD,
  BM_MOD,
};

class CRenderer;
class MRAGPP_EXPORT CTexture
{
public:
  CRenderer* tex_pRenderer;
  SDL_Texture* tex_pTexture;
  int tex_iWidth;
  int tex_iHeight;
  unsigned int tex_iFormat;
  int tex_iAccess;
  bool tex_bLoaded;

private:
  COLOR_VALUE tex_iLastAlpha;
  ETextureBlendMode tex_ebmLastBlendMode;
  COLOR tex_colLast;

public:
  CTexture();
  CTexture(SDL_Texture* pTexture);
  CTexture(CRenderer &renderer, const char* szFilename);
  ~CTexture();

  void QueryTextureInfo();

  void Load(CRenderer &renderer, const char* szFilename);
  void LoadFromPointer(CRenderer &renderer, unsigned char* pubBuffer, unsigned int iLen);
#ifdef _MSC_VER
  void LoadFromResource(CRenderer &renderer, int iResID);
#endif

  void SetAlphaMod(COLOR_VALUE alpha);
  void SetBlendingMode(ETextureBlendMode ebm);
  void SetColorMod(COLOR col);

  void Destroy();

  operator SDL_Texture*();
};

MRAGPP_NAMESPACE_END;

#endif
