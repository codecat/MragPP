#ifndef MRAGPP_FONT_H_INCLUDED
#define MRAGPP_FONT_H_INCLUDED

#include "StdH.h"

struct _TTF_Font;
typedef struct _TTF_Font TTF_Font;

MRAGPP_NAMESPACE_BEGIN;

class MRAGPP_EXPORT CFont
{
private:
  TTF_Font* fnt_pFont;

public:
  CFont();
  CFont(TTF_Font* pFont);
  ~CFont();

  void Load(const char* szFilename, int iPtSize);
  void LoadFromPointer(unsigned char* pubBuffer, unsigned int iLen, int iPtSize);
#ifdef _MSC_VER
  void LoadFromResource(int iResID, int iPtSize);
#endif
  void Destroy();

  operator TTF_Font*();
};

MRAGPP_NAMESPACE_END;

#endif
