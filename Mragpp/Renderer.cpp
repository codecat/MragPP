#include "StdH.h"
#include "Renderer.h"
#include "Window.h"
#include "Rectangle.h"
#include "Matrix.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <GL/glew.h>

MRAGPP_NAMESPACE_BEGIN;

CRenderer::CRenderer()
{
  ren_pRenderer = 0;
  ren_colCurrentColor = COL_BLACK | MRAG_ALPHA_OPAQUE;
  ren_pfntCurrentFont = 0;
  ren_bTextShadow = FALSE;
  ren_matTransform = IDENTITY_MATRIX;
}

CRenderer::CRenderer(SDL_Renderer* pRenderer)
{
  ren_pRenderer = pRenderer;
}

CRenderer::~CRenderer()
{
  Destroy();
}

void CRenderer::Create(CWindow &window)
{
  ren_pRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
  glEnable(GL_MULTISAMPLE);

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

  static bool _bInitializedGlew = false;
  if(!_bInitializedGlew) {
    GLenum err = glewInit();
    if(err != GLEW_OK) {
      printf("Glew initialization error: %d\n", err);
    }
    _bInitializedGlew = true;
  }

  if(ren_pRenderer == 0) {
    printf("SDL renderer creation error: '%s'\n", SDL_GetError());
    return;
  }
}

void CRenderer::Destroy()
{
  if(ren_pRenderer == 0) {
    return;
  }

  SDL_DestroyRenderer(ren_pRenderer);
  ren_pRenderer = 0;
}

CRenderer::operator SDL_Renderer*()
{
  return ren_pRenderer;
}

void CRenderer::SetColor(COLOR c)
{
  ren_colCurrentColor = c;
  SDL_SetRenderDrawColor(ren_pRenderer,
    (Uint8)((c & 0xFF000000) >> 24),
    (Uint8)((c & 0x00FF0000) >> 16),
    (Uint8)((c & 0x0000FF00) >> 8),
    (Uint8)((c & 0x000000FF)));
}

void CRenderer::PushColor(COLOR color)
{
  ren_colPreviousColor = ren_colCurrentColor;
  SetColor(color);
}

void CRenderer::PopColor()
{
  SetColor(ren_colPreviousColor);
}

void CRenderer::SetFont(CFont &font)
{
  ren_pfntCurrentFont = &font;
}

void CRenderer::PushFont(CFont &font)
{
  ren_pfntPreviousFont = ren_pfntCurrentFont;
  ren_pfntCurrentFont = &font;
}

void CRenderer::PopFont()
{
  ren_pfntCurrentFont = ren_pfntPreviousFont;
}

void CRenderer::Clear()
{
  SDL_RenderClear(ren_pRenderer);
  SDL_RenderFillRect(ren_pRenderer, NULL);
}

template<typename T>
void CRenderer::TransformPosition(T &x, T &y)
{
  ren_matTransform.SetTransform(x, y);
}

template<typename T>
void CRenderer::TransformPosition(T &x, T &y, T &w, T &h)
{
  ren_matTransform.SetTransform(x, y);
  ren_matTransform.SetTransform(w, h);
}

void CRenderer::FillRectangle(float x, float y, float width, float height)
{
  SDL_Rect r;
  r.x = (int)x;
  r.y = (int)y;
  r.w = (int)width;
  r.h = (int)height;

  TransformPosition(r.x, r.y, r.w, r.h);

  SDL_SetRenderDrawBlendMode(ren_pRenderer, SDL_BLENDMODE_BLEND);
  SDL_RenderFillRect(ren_pRenderer, &r);
}

void CRenderer::FillRectangle(const CRectangle &rect)
{
  SDL_Rect r = rect.GetSDLRect();
  TransformPosition(r.x, r.y, r.w, r.h);

  //TODO: Support rect rotation here
  SDL_SetRenderDrawBlendMode(ren_pRenderer, SDL_BLENDMODE_BLEND);
  SDL_RenderFillRect(ren_pRenderer, &r);
}

void CRenderer::PutRectangle(float x, float y, float width, float height)
{
  SDL_Rect r;
  r.x = (int)x;
  r.y = (int)y;
  r.w = (int)width;
  r.h = (int)height;

  TransformPosition(r.x, r.y, r.w, r.h);

  SDL_RenderDrawRect(ren_pRenderer, &r);
}

void CRenderer::PutRectangle(const CRectangle &rect)
{
  Vector2f points[5];
  rect.GetRotatedPosArray(points);
  points[4] = points[0];
  PutLines(points, 5);
}

void CRenderer::PutLine(float ax, float ay, float bx, float by)
{
  TransformPosition(ax, ay);
  TransformPosition(bx, by);

  SDL_RenderDrawLine(ren_pRenderer, (int)ax, (int)ay, (int)bx, (int)by);
}

void CRenderer::PutLine(Vector2f vPointA, Vector2f vPointB)
{
  TransformPosition(vPointA(1), vPointA(2));
  TransformPosition(vPointB(1), vPointB(2));

  SDL_RenderDrawLine(ren_pRenderer, (int)vPointA(1), (int)vPointA(2), (int)vPointB(1), (int)vPointB(2));
}

void CRenderer::PutLines(const Vector2f* pPoints, int ctPoints)
{
  SDL_Point* p = new SDL_Point[ctPoints];
  for(int i=0; i<ctPoints; i++) {
    p[i].x = (int)pPoints[i](1);
    p[i].y = (int)pPoints[i](2);
    TransformPosition(p[i].x, p[i].y);
  }
  SDL_RenderDrawLines(ren_pRenderer, p, ctPoints);
  delete[] p;
}

void CRenderer::PutLines(const SPoint2f* pPoints, int ctPoints)
{
  SDL_Point* p = new SDL_Point[ctPoints];
  for(int i=0; i<ctPoints; i++) {
    p[i].x = (int)pPoints[i].x;
    p[i].y = (int)pPoints[i].y;
    TransformPosition(p[i].x, p[i].y);
  }
  SDL_RenderDrawLines(ren_pRenderer, p, ctPoints);
  delete[] p;
}

void CRenderer::PutPolygon(const Vector2f* pPoints, int ctPoints)
{
  SDL_Point* p = new SDL_Point[ctPoints+1];
  for(int i=0; i<ctPoints+1; i++) {
    int j = i == ctPoints ? 0 : i;
    p[i].x = (int)pPoints[j](1);
    p[i].y = (int)pPoints[j](2);
    TransformPosition(p[i].x, p[i].y);
  }
  SDL_RenderDrawLines(ren_pRenderer, p, ctPoints+1);
  delete[] p;
}

void CRenderer::PutPolygon(const SPoint2f* pPoints, int ctPoints)
{
  SDL_Point* p = new SDL_Point[ctPoints+1];
  for(int i=0; i<ctPoints+1; i++) {
    int j = i == ctPoints ? 0 : i;
    p[i].x = (int)pPoints[j].x;
    p[i].y = (int)pPoints[j].y;
    TransformPosition(p[i].x, p[i].y);
  }
  SDL_RenderDrawLines(ren_pRenderer, p, ctPoints+1);
  delete[] p;
}

void CRenderer::PutTexture(CTexture &texture, float x, float y)
{
  SDL_Rect r;
  r.x = (int)x;
  r.y = (int)y;
  r.w = texture.tex_iWidth;
  r.h = texture.tex_iHeight;

  TransformPosition(r.x, r.y, r.w, r.h);

  SDL_RenderCopy(ren_pRenderer, texture, 0, &r);
}

void CRenderer::PutTexture(CTexture &texture, float x, float y, float width, float height)
{
  SDL_Rect r;
  r.x = (int)x;
  r.y = (int)y;
  r.w = (int)width;
  r.h = (int)height;

  TransformPosition(r.x, r.y, r.w, r.h);

  SDL_RenderCopy(ren_pRenderer, texture, 0, &r);
}

void CRenderer::PutTexture(CTexture &texture, float x, float y, float width, float height, float rot)
{
  SDL_Rect r;
  r.x = (int)x;
  r.y = (int)y;
  r.w = (int)width;
  r.h = (int)height;

  TransformPosition(r.x, r.y, r.w, r.h);

  Vector2i vCenter((int)(width/2), (int)(height/2));
  TransformPosition(vCenter(1), vCenter(2));

  SDL_RenderCopyEx(ren_pRenderer, texture, 0, &r, (double)rot, (SDL_Point*)&vCenter, SDL_FLIP_NONE);
}

void CRenderer::PutTexture(CTexture &texture, float x, float y, float width, float height, float rot, bool bFlipHor, bool bFlipVer)
{
  SDL_Rect r;
  r.x = (int)x;
  r.y = (int)y;
  r.w = (int)width;
  r.h = (int)height;

  TransformPosition(r.x, r.y, r.w, r.h);

  Vector2i vCenter((int)(width/2), (int)(height/2));
  TransformPosition(vCenter(1), vCenter(2));

  int flip = SDL_FLIP_NONE;
  if(bFlipHor) { flip |= SDL_FLIP_HORIZONTAL; }
  if(bFlipVer) { flip |= SDL_FLIP_VERTICAL; }

  SDL_RenderCopyEx(ren_pRenderer, texture, 0, &r, (double)rot, (SDL_Point*)&vCenter, (SDL_RendererFlip)flip);
}

void CRenderer::PutTexture(CTexture &texture, float x, float y, float width, float height, float rot, Vector2f vCenter, bool centerOffset, bool bFlipHor, bool bFlipVer)
{
  SDL_Rect r;
  r.x = (int)x;
  r.y = (int)y;
  r.w = (int)width;
  r.h = (int)height;

  TransformPosition(r.x, r.y, r.w, r.h);

  if(centerOffset) {
    vCenter(1) = width / 2.0f;
    vCenter(2) = height / 2.0f;
  }
  TransformPosition(vCenter(1), vCenter(2));

  int flip = SDL_FLIP_NONE;
  if(bFlipHor) { flip |= SDL_FLIP_HORIZONTAL; }
  if(bFlipVer) { flip |= SDL_FLIP_VERTICAL; }

  Vector2i vec = vCenter.GetAs<2,int>();
  SDL_RenderCopyEx(ren_pRenderer, texture, 0, &r, (double)rot, (SDL_Point*)&vec, (SDL_RendererFlip)flip);
}

void CRenderer::PutTexture(CTexture &texture, const CRectangle &rectDest)
{
  float x = rectDest.x;
  float y = rectDest.y;

  if(rectDest.anchorInCenter) {
    x -= rectDest.w / 2;
    y -= rectDest.h / 2;
  }

  PutTexture(texture, x, y, rectDest.w, rectDest.h, rectDest.rotation);
}

void CRenderer::PutTexture(CTexture &texture, const CRectangle &rectDest, const CRectangle &rectSrc, bool bFlipHor, bool bFlipVer)
{
  SDL_Rect dest = rectDest.GetSDLRect();
  const SDL_Rect src = rectSrc.GetSDLRect();

  if(rectDest.anchorInCenter) {
    dest.x -= dest.w / 2;
    dest.y -= dest.h / 2;
  }

  TransformPosition(dest.x, dest.y, dest.w, dest.h);

  Vector2i vCenter((int)(rectDest.w/2), (int)(rectDest.h/2));
  TransformPosition(vCenter(1), vCenter(2));

  int flip = SDL_FLIP_NONE;
  if(bFlipHor) { flip |= SDL_FLIP_HORIZONTAL; }
  if(bFlipVer) { flip |= SDL_FLIP_VERTICAL; }

  SDL_RenderCopyEx(ren_pRenderer, texture, &src, &dest, (float)rectDest.rotation, (SDL_Point*)&vCenter, (SDL_RendererFlip)flip);
}

void CRenderer::PutTextureCenter(CTexture &texture, float x, float y)
{
  SDL_Rect r;
  r.x = (int)(x - texture.tex_iWidth / 2);
  r.y = (int)(y - texture.tex_iHeight / 2);
  r.w = (int)texture.tex_iWidth;
  r.h = (int)texture.tex_iHeight;

  TransformPosition(r.x, r.y, r.w, r.h);

  SDL_RenderCopy(ren_pRenderer, texture, 0, &r);
}

void CRenderer::PutTextureCenter(CTexture &texture, float x, float y, float width, float height)
{
  SDL_Rect r;
  r.x = (int)(x - width / 2);
  r.y = (int)(y - height / 2);
  r.w = (int)width;
  r.h = (int)height;

  TransformPosition(r.x, r.y, r.w, r.h);

  SDL_RenderCopy(ren_pRenderer, texture, 0, &r);
}

void CRenderer::PutTextureCenter(CTexture &texture, float x, float y, float width, float height, float rot)
{
  SDL_Rect r;
  r.x = (int)(x - width / 2);
  r.y = (int)(y - height / 2);
  r.w = (int)width;
  r.h = (int)height;

  TransformPosition(r.x, r.y, r.w, r.h);

  Vector2i vCenter((int)(width/2), (int)(height/2));
  TransformPosition(vCenter(1), vCenter(2));

  SDL_RenderCopyEx(ren_pRenderer, texture, 0, &r, (double)rot, (SDL_Point*)&vCenter, SDL_FLIP_NONE);
}

void CRenderer::PutTextureCenter(CTexture &texture, float x, float y, float width, float height, float rot, bool bFlipHor, bool bFlipVer)
{
  SDL_Rect r;
  r.x = (int)(x - width / 2);
  r.y = (int)(y - height / 2);
  r.w = (int)width;
  r.h = (int)height;

  TransformPosition(r.x, r.y, r.w, r.h);

  Vector2i vCenter((int)(width/2), (int)(height/2));
  TransformPosition(vCenter(1), vCenter(2));

  int flip = SDL_FLIP_NONE;
  if(bFlipHor) { flip |= SDL_FLIP_HORIZONTAL; }
  if(bFlipVer) { flip |= SDL_FLIP_VERTICAL; }

  SDL_RenderCopyEx(ren_pRenderer, texture, 0, &r, (double)rot, (SDL_Point*)&vCenter, (SDL_RendererFlip)flip);
}

void CRenderer::PutTextureCenter(CTexture &texture, float x, float y, float width, float height, float rot, Vector2f vCenter, bool centerOffset, bool bFlipHor, bool bFlipVer)
{
  SDL_Rect r;
  r.x = (int)(x - width / 2);
  r.y = (int)(y - height / 2);
  r.w = (int)width;
  r.h = (int)height;

  TransformPosition(r.x, r.y, r.w, r.h);

  if(centerOffset) {
    vCenter(1) = width / 2.0f;
    vCenter(2) = height / 2.0f;
  }
  TransformPosition(vCenter(1), vCenter(2));

  int flip = SDL_FLIP_NONE;
  if(bFlipHor) { flip |= SDL_FLIP_HORIZONTAL; }
  if(bFlipVer) { flip |= SDL_FLIP_VERTICAL; }

  Vector2i vec = vCenter.GetAs<2,int>();
  SDL_RenderCopyEx(ren_pRenderer, texture, 0, &r, (double)rot, (SDL_Point*)&vec, (SDL_RendererFlip)flip);
}

void CRenderer::PutTextureRight(CTexture &texture, float x, float y)
{
  SDL_Rect r;
  r.x = (int)(x - texture.tex_iWidth);
  r.y = (int)y;
  r.w = (int)texture.tex_iWidth;
  r.h = (int)texture.tex_iHeight;

  TransformPosition(r.x, r.y, r.w, r.h);

  SDL_RenderCopy(ren_pRenderer, texture, 0, &r);
}

void CRenderer::PutTextureRight(CTexture &texture, float x, float y, float width, float height)
{
  SDL_Rect r;
  r.x = (int)(x - width);
  r.y = (int)y;
  r.w = (int)width;
  r.h = (int)height;

  TransformPosition(r.x, r.y, r.w, r.h);

  SDL_RenderCopy(ren_pRenderer, texture, 0, &r);
}

void CRenderer::PutTextureRight(CTexture &texture, float x, float y, float width, float height, float rot)
{
  SDL_Rect r;
  r.x = (int)(x - width);
  r.y = (int)y;
  r.w = (int)width;
  r.h = (int)height;

  TransformPosition(r.x, r.y, r.w, r.h);

  Vector2i vCenter((int)(width/2), (int)(height/2));
  TransformPosition(vCenter(1), vCenter(2));

  SDL_RenderCopyEx(ren_pRenderer, texture, 0, &r, (double)rot, (SDL_Point*)&vCenter, SDL_FLIP_NONE);
}

void CRenderer::PutTextureRight(CTexture &texture, float x, float y, float width, float height, float rot, bool bFlipHor, bool bFlipVer)
{
  SDL_Rect r;
  r.x = (int)(x - width);
  r.y = (int)y;
  r.w = (int)width;
  r.h = (int)height;

  TransformPosition(r.x, r.y, r.w, r.h);

  Vector2i vCenter((int)(width/2), (int)(height/2));
  TransformPosition(vCenter(1), vCenter(2));

  int flip = SDL_FLIP_NONE;
  if(bFlipHor) { flip |= SDL_FLIP_HORIZONTAL; }
  if(bFlipVer) { flip |= SDL_FLIP_VERTICAL; }

  SDL_RenderCopyEx(ren_pRenderer, texture, 0, &r, (double)rot, (SDL_Point*)&vCenter, (SDL_RendererFlip)flip);
}

void CRenderer::PutTextureRight(CTexture &texture, float x, float y, float width, float height, float rot, Vector2f vCenter, bool centerOffset, bool bFlipHor, bool bFlipVer)
{
  SDL_Rect r;
  r.x = (int)(x - width);
  r.y = (int)y;
  r.w = (int)width;
  r.h = (int)height;

  TransformPosition(r.x, r.y, r.w, r.h);

  if(centerOffset) {
    vCenter(1) = width / 2.0f;
    vCenter(2) = height / 2.0f;
  }
  TransformPosition(vCenter(1), vCenter(2));

  int flip = SDL_FLIP_NONE;
  if(bFlipHor) { flip |= SDL_FLIP_HORIZONTAL; }
  if(bFlipVer) { flip |= SDL_FLIP_VERTICAL; }

  Vector2i vec = vCenter.GetAs<2,int>();
  SDL_RenderCopyEx(ren_pRenderer, texture, 0, &r, (double)rot, (SDL_Point*)&vec, (SDL_RendererFlip)flip);
}

void CRenderer::MakeTextTexture(CTexture &texture, const Scratch::String &strText, COLOR col)
{
  SDL_Color colSet;
  MRAG_COLOR_EXPLODE_RGBA(col, colSet.r, colSet.g, colSet.b, colSet.a);

  if(*ren_pfntCurrentFont == NULL) {
    return;
  }

  SDL_Surface* pSurface = TTF_RenderText_Blended(*ren_pfntCurrentFont, strText, colSet);
  SDL_Texture* pTexture = SDL_CreateTextureFromSurface(ren_pRenderer, pSurface);
  SDL_FreeSurface(pSurface);
  if(texture.tex_pTexture != NULL) {
    texture.Destroy();
  }
  texture.tex_pTexture = pTexture;
  texture.QueryTextureInfo();
}

void CRenderer::PutText(const Scratch::String &strText, float x, float y)
{
  if(ren_pfntCurrentFont == 0) {
    return;
  }

  CTexture tex;
  MakeTextTexture(tex, strText, ren_colCurrentColor);
  if(ren_bTextShadow) {
    tex.SetColorMod(0x000000FF);
    PutTexture(tex, x + 1, y + 1);
    tex.SetColorMod(0xFFFFFFFF);
  }
  PutTexture(tex, x, y);
}

void CRenderer::PutText(const Scratch::String &strText, float x, float y, float rot)
{
  if(ren_pfntCurrentFont == 0) {
    return;
  }

  CTexture tex;
  MakeTextTexture(tex, strText, ren_colCurrentColor);
  if(ren_bTextShadow) {
    tex.SetColorMod(0x000000FF);
    PutTexture(tex, x + 1, y + 1, (float)tex.tex_iWidth, (float)tex.tex_iHeight, rot);
    tex.SetColorMod(0xFFFFFFFF);
  }
  PutTexture(tex, x, y, (float)tex.tex_iWidth, (float)tex.tex_iHeight, rot);
}

void CRenderer::PutText(const Scratch::String &strText, float x, float y, float rot, const Vector2f &vCenter)
{
  if(ren_pfntCurrentFont == 0) {
    return;
  }

  CTexture tex;
  MakeTextTexture(tex, strText, ren_colCurrentColor);
  if(ren_bTextShadow) {
    tex.SetColorMod(0x000000FF);
    PutTexture(tex, x + 1, y + 1, (float)tex.tex_iWidth, (float)tex.tex_iHeight, rot, vCenter, true);
    tex.SetColorMod(0xFFFFFFFF);
  }
  PutTexture(tex, x, y, (float)tex.tex_iWidth, (float)tex.tex_iHeight, rot, vCenter, true);
}

void CRenderer::PutTextColored(const Scratch::String &strText, float x, float y, COLOR col)
{
  if(ren_pfntCurrentFont == 0) {
    return;
  }

  CTexture tex;
  MakeTextTexture(tex, strText, col);
  if(ren_bTextShadow) {
    tex.SetColorMod(0x000000FF);
    PutTexture(tex, x + 1, y + 1);
    tex.SetColorMod(0xFFFFFFFF);
  }
  PutTexture(tex, x, y);
}

void CRenderer::PutTextColored(const Scratch::String &strText, float x, float y, float rot, COLOR col)
{
  if(ren_pfntCurrentFont == 0) {
    return;
  }

  CTexture tex;
  MakeTextTexture(tex, strText, col);
  if(ren_bTextShadow) {
    tex.SetColorMod(0x000000FF);
    PutTexture(tex, x + 1, y + 1, (float)tex.tex_iWidth, (float)tex.tex_iHeight, rot);
    tex.SetColorMod(0xFFFFFFFF);
  }
  PutTexture(tex, x, y, (float)tex.tex_iWidth, (float)tex.tex_iHeight, rot);
}

void CRenderer::PutTextColored(const Scratch::String &strText, float x, float y, float rot, const Vector2f &vCenter, COLOR col)
{
  if(ren_pfntCurrentFont == 0) {
    return;
  }

  CTexture tex;
  MakeTextTexture(tex, strText, col);
  if(ren_bTextShadow) {
    tex.SetColorMod(0x000000FF);
    PutTexture(tex, x + 1, y + 1,  (float)tex.tex_iWidth, (float)tex.tex_iHeight, rot, vCenter, true);
    tex.SetColorMod(0xFFFFFFFF);
  }
  PutTexture(tex, x, y, (float)tex.tex_iWidth, (float)tex.tex_iHeight, rot, vCenter, true);
}

void CRenderer::PutTextCenter(const Scratch::String &strText, float x, float y)
{
  if(ren_pfntCurrentFont == 0) {
    return;
  }

  CTexture tex;
  MakeTextTexture(tex, strText, ren_colCurrentColor);
  if(ren_bTextShadow) {
    tex.SetColorMod(0x000000FF);
    PutTextureCenter(tex, x + 1, y + 1);
    tex.SetColorMod(0xFFFFFFFF);
  }
  PutTextureCenter(tex, x, y);
}

void CRenderer::PutTextCenter(const Scratch::String &strText, float x, float y, float rot)
{
  if(ren_pfntCurrentFont == 0) {
    return;
  }

  CTexture tex;
  MakeTextTexture(tex, strText, ren_colCurrentColor);
  if(ren_bTextShadow) {
    tex.SetColorMod(0x000000FF);
    PutTextureCenter(tex, x + 1, y + 1, (float)tex.tex_iWidth, (float)tex.tex_iHeight, rot);
    tex.SetColorMod(0xFFFFFFFF);
  }
  PutTextureCenter(tex, x, y, (float)tex.tex_iWidth, (float)tex.tex_iHeight, rot);
}

void CRenderer::PutTextCenter(const Scratch::String &strText, float x, float y, float rot, const Vector2f &vCenter)
{
  if(ren_pfntCurrentFont == 0) {
    return;
  }

  CTexture tex;
  MakeTextTexture(tex, strText, ren_colCurrentColor);
  if(ren_bTextShadow) {
    tex.SetColorMod(0x000000FF);
    PutTextureCenter(tex, x + 1, y + 1);
    tex.SetColorMod(0xFFFFFFFF);
  }
  PutTextureCenter(tex, x, y, (float)tex.tex_iWidth, (float)tex.tex_iHeight, rot, vCenter, true);
}

void CRenderer::PutTextRight(const Scratch::String &strText, float x, float y)
{
  if(ren_pfntCurrentFont == 0) {
    return;
  }

  CTexture tex;
  MakeTextTexture(tex, strText, ren_colCurrentColor);
  if(ren_bTextShadow) {
    tex.SetColorMod(0x000000FF);
    PutTextureRight(tex, x + 1, y + 1);
    tex.SetColorMod(0xFFFFFFFF);
  }
  PutTextureRight(tex, x, y);
}

void CRenderer::PutTextRight(const Scratch::String &strText, float x, float y, float rot)
{
  if(ren_pfntCurrentFont == 0) {
    return;
  }

  CTexture tex;
  MakeTextTexture(tex, strText, ren_colCurrentColor);
  if(ren_bTextShadow) {
    tex.SetColorMod(0x000000FF);
    PutTextureRight(tex, x + 1, y + 1);
    tex.SetColorMod(0xFFFFFFFF);
  }
  PutTextureRight(tex, x, y, (float)tex.tex_iWidth, (float)tex.tex_iHeight, rot);
}

void CRenderer::PutTextRight(const Scratch::String &strText, float x, float y, float rot, const Vector2f &vCenter)
{
  if(ren_pfntCurrentFont == 0) {
    return;
  }

  CTexture tex;
  MakeTextTexture(tex, strText, ren_colCurrentColor);
  if(ren_bTextShadow) {
    tex.SetColorMod(0x000000FF);
    PutTextureRight(tex, x + 1, y + 1);
    tex.SetColorMod(0xFFFFFFFF);
  }
  PutTextureRight(tex, x, y, (float)tex.tex_iWidth, (float)tex.tex_iHeight, rot, vCenter, true);
}

void CRenderer::Present()
{
  SDL_RenderPresent(ren_pRenderer);
}

MRAGPP_NAMESPACE_END;
