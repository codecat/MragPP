#ifndef MRAGPP_RENDERER_H_INCLUDED
#define MRAGPP_RENDERER_H_INCLUDED

#include "StdH.h"
#include "Window.h"
#include "Texture.h"
#include "Font.h"
#include "Rectangle.h"
#include "Matrix.h"

struct SDL_Renderer;

MRAGPP_NAMESPACE_BEGIN;

struct SPoint2f
{
  float x, y;
};

class MRAGPP_EXPORT CRenderer
{
private:
  SDL_Renderer* ren_pRenderer;

  COLOR ren_colCurrentColor;
  COLOR ren_colPreviousColor;

  CFont* ren_pfntCurrentFont;
  CFont* ren_pfntPreviousFont;

public:
  CMatrix ren_matTransform;

  BOOL ren_bTextShadow;

public:
  CRenderer();
  CRenderer(SDL_Renderer* pRenderer);
  ~CRenderer();

  void Create(CWindow &window);
  void Destroy();

  operator SDL_Renderer*();

  void SetColor(COLOR color);
  void PushColor(COLOR color); // the stack size is 2. it remembers only the previous state.
  void PopColor();

  void SetFont(CFont &font);
  void PushFont(CFont &font); // the stack size of 2. it remembers only the previous state.
  void PopFont();

  void Clear();

  template<typename T> void TransformPosition(T &x, T &y);
  template<typename T> void TransformPosition(T &x, T &y, T &w, T &h);

  void FillRectangle(float x, float y, float width, float height);
  void FillRectangle(const CRectangle &rect);
  void PutRectangle(float x, float y, float width, float height);
  void PutRectangle(const CRectangle &rect);

  void PutLine(float ax, float ay, float bx, float by);
  void PutLine(Vector2f vPointA, Vector2f vPointB);
  void PutLines(const Vector2f* pPoints, int ctPoints);
  void PutLines(const SPoint2f* pPoints, int ctPoints);

  void PutPolygon(const Vector2f* pPoints, int ctPoints);
  void PutPolygon(const SPoint2f* pPoints, int ctPoints);

  void PutTexture(CTexture &texture, float x, float y);
  void PutTexture(CTexture &texture, float x, float y, float width, float height);
  void PutTexture(CTexture &texture, float x, float y, float width, float height, float rot);
  void PutTexture(CTexture &texture, float x, float y, float width, float height, float rot, bool bFlipHor, bool bFlipVer);
  void PutTexture(CTexture &texture, float x, float y, float width, float height, float rot, Vector2f vCenter, bool centerOffset = false, bool bFlipHor = false, bool bFlipVer = false);

  void PutTexture(CTexture &texture, const CRectangle &rectDest);
  void PutTexture(CTexture &texture, const CRectangle &rectDest, const CRectangle &rectSrc, bool bFlipHor = false, bool bFlipVer = false);

  void PutTextureCenter(CTexture &texture, float x, float y);
  void PutTextureCenter(CTexture &texture, float x, float y, float width, float height);
  void PutTextureCenter(CTexture &texture, float x, float y, float width, float height, float rot);
  void PutTextureCenter(CTexture &texture, float x, float y, float width, float height, float rot, bool bFlipHor, bool bFlipVer);
  void PutTextureCenter(CTexture &texture, float x, float y, float width, float height, float rot, Vector2f vCenter, bool centerOffset = false, bool bFlipHor = false, bool bFlipVer = false);

  void PutTextureRight(CTexture &texture, float x, float y);
  void PutTextureRight(CTexture &texture, float x, float y, float width, float height);
  void PutTextureRight(CTexture &texture, float x, float y, float width, float height, float rot);
  void PutTextureRight(CTexture &texture, float x, float y, float width, float height, float rot, bool bFlipHor, bool bFlipVer);
  void PutTextureRight(CTexture &texture, float x, float y, float width, float height, float rot, Vector2f vCenter, bool centerOffset = false, bool bFlipHor = false, bool bFlipVer = false);

  void MakeTextTexture(CTexture &texture, const Scratch::CString &strText, COLOR col);

  void PutText(const Scratch::CString &strText, float x, float y);
  void PutText(const Scratch::CString &strText, float x, float y, float rot);
  void PutText(const Scratch::CString &strText, float x, float y, float rot, const Vector2f &vCenter);

  void PutTextColored(const Scratch::CString &strText, float x, float y, COLOR col);
  void PutTextColored(const Scratch::CString &strText, float x, float y, float rot, COLOR col);
  void PutTextColored(const Scratch::CString &strText, float x, float y, float rot, const Vector2f &vCenter, COLOR col);

  void PutTextCenter(const Scratch::CString &strText, float x, float y);
  void PutTextCenter(const Scratch::CString &strText, float x, float y, float rot);
  void PutTextCenter(const Scratch::CString &strText, float x, float y, float rot, const Vector2f &vCenter);

  void PutTextRight(const Scratch::CString &strText, float x, float y);
  void PutTextRight(const Scratch::CString &strText, float x, float y, float rot);
  void PutTextRight(const Scratch::CString &strText, float x, float y, float rot, const Vector2f &vCenter);

  void Present();
};

MRAGPP_NAMESPACE_END;

#endif
