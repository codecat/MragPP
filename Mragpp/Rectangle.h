#ifndef MRAGPP_RECTANGLE_H_INCLUDED
#define MRAGPP_RECTANGLE_H_INCLUDED

#include "StdH.h"

struct SDL_Rect;

MRAGPP_NAMESPACE_BEGIN;

class MRAGPP_EXPORT CRectangle
{
public:
  float x;
  float y;
  float w;
  float h;

  float rotation;
  bool anchorInCenter;

public:
  CRectangle();
  CRectangle(Vector2f vPos, Vector2f vSize);
  CRectangle(Vector2f vPos, Vector2f vSize, float fRot);
  CRectangle(float fX, float fY, float fW, float fH);
  CRectangle(float fX, float fY, float fW, float fH, float fRot);
  CRectangle(const SDL_Rect &rect);
  ~CRectangle();

  Scratch::CString ToString();

  void Translate(const Vector2f &v);
  void Rotate(float fDegrees);

  Vector2f GetPos() const;
  Vector2f GetSize() const;

  void GetRotatedPosArray(Vector2f* pArray) const; // requires array size of at least (typeof(Vector2f)*4)

  bool Contains(const Vector2f &point);
  bool Contains(const Vector2i &point);

  bool Intersects(const CRectangle &other);

  SDL_Rect GetSDLRect() const;

  static bool PointInPolygon(const Vector2f &p, const Vector2f* poly, int vertices);
};

inline CRectangle ParseRectangle(const Scratch::CString &str)
{
  Scratch::CStackArray<Scratch::CString> parse;
  str.Split(",", parse, TRUE);

  CRectangle ret;

  if(parse.Count() >= 2) {
    ret.x = (float)atof(parse[0]);
    ret.y = (float)atof(parse[1]);
  }

  if(parse.Count() >= 4) {
    ret.w = (float)atof(parse[2]);
    ret.h = (float)atof(parse[3]);
  }

  return ret;
}

MRAGPP_NAMESPACE_END;

#endif
