#include "StdH.h"
#include "Rectangle.h"
#include "Matrix.h"

#include <SDL.h>

MRAGPP_NAMESPACE_BEGIN;

CRectangle::CRectangle()
{
  x = y = w = h = 0;
  rotation = 0;
  anchorInCenter = false;
}

CRectangle::CRectangle(float fX, float fY, float fW, float fH)
{
  x = fX; y = fY;
  w = fW; h = fH;
  rotation = 0;
  anchorInCenter = false;
}

CRectangle::CRectangle(float fX, float fY, float fW, float fH, float fRot)
{
  x = fX; y = fY;
  w = fW; h = fH;
  rotation = fRot;
  anchorInCenter = false;
}

CRectangle::CRectangle(const SDL_Rect &rect)
{
  x = (float)rect.x; y = (float)rect.y;
  w = (float)rect.w; h = (float)rect.h;
  rotation = 0;
  anchorInCenter = false;
}

CRectangle::~CRectangle()
{
}

Scratch::CString CRectangle::ToString()
{
  Scratch::CString ret;
  ret.SetF("{%d, %d, %d, %d}", x, y, w, h);
  return ret;
}

void CRectangle::Translate(const Vector2f &v)
{
  x += v(1);
  y += v(2);
}

void CRectangle::Rotate(float fDegrees)
{
  rotation += fDegrees;
}

Vector2f CRectangle::GetPos() const
{
  return Vector2f(x, y);
}

Vector2f CRectangle::GetSize() const
{
  return Vector2f(w, h);
}

void CRectangle::GetRotatedPosArray(Vector2f* pArray) const
{
  ASSERT(pArray != NULL);

  CMatrix mat = CMatrix::CreateRotationZ(mthToRadians(rotation));

  Vector2f &topLeft = pArray[0];
  Vector2f &topRight = pArray[1];
  Vector2f &botRight = pArray[2];
  Vector2f &botLeft = pArray[3];

  Vector2f pos = GetPos().GetAs<2,float>();

  if(anchorInCenter) {
    topLeft = pos + mat.Transform(Vector2f(-w/2, -h/2));
    topRight = pos + mat.Transform(Vector2f(w/2, -h/2));
    botRight = pos + mat.Transform(Vector2f(w/2, h/2));
    botLeft = pos + mat.Transform(Vector2f(-w/2, h/2));
  } else {
    topLeft = pos;
    topRight = pos + mat.Transform(Vector2f(w, 0));
    botRight = pos + mat.Transform(Vector2f(w, h));
    botLeft = pos + mat.Transform(Vector2f(0, h));
  }
}

bool CRectangle::Contains(const Vector2f &point)
{
  Vector2f verts[4];
  GetRotatedPosArray(verts);
  return PointInPolygon(point, verts, 4);
}

bool CRectangle::Contains(const Vector2i &point)
{
  return Contains(point.GetAs<2,float>());
}

bool CRectangle::Intersects(const CRectangle &other)
{
  Vector2f points[4]; GetRotatedPosArray(points);
  Vector2f otherPoints[4]; other.GetRotatedPosArray(otherPoints);

  if(PointInPolygon(points[0], otherPoints, 4)) {
    return true; }
  if(PointInPolygon(points[1], otherPoints, 4)) {
    return true; }
  if(PointInPolygon(points[2], otherPoints, 4)) {
    return true; }
  if(PointInPolygon(points[3], otherPoints, 4)) {
    return true; }

  if(PointInPolygon(otherPoints[0], points, 4)) {
    return true; }
  if(PointInPolygon(otherPoints[1], points, 4)) {
    return true; }
  if(PointInPolygon(otherPoints[2], points, 4)) {
    return true; }
  if(PointInPolygon(otherPoints[3], points, 4)) {
    return true; }

  if (mthLineSegmentsIntersect(points[0], points[1], otherPoints[0], otherPoints[1]) ||
      mthLineSegmentsIntersect(points[1], points[2], otherPoints[0], otherPoints[1]) ||
      mthLineSegmentsIntersect(points[2], points[3], otherPoints[0], otherPoints[1]) ||
      mthLineSegmentsIntersect(points[3], points[0], otherPoints[0], otherPoints[1]) ||
      mthLineSegmentsIntersect(points[0], points[1], otherPoints[1], otherPoints[2]) ||
      mthLineSegmentsIntersect(points[1], points[2], otherPoints[1], otherPoints[2]) ||
      mthLineSegmentsIntersect(points[2], points[3], otherPoints[1], otherPoints[2]) ||
      mthLineSegmentsIntersect(points[3], points[0], otherPoints[1], otherPoints[2]) ||
      mthLineSegmentsIntersect(points[0], points[1], otherPoints[2], otherPoints[3]) ||
      mthLineSegmentsIntersect(points[1], points[2], otherPoints[2], otherPoints[3]) ||
      mthLineSegmentsIntersect(points[2], points[3], otherPoints[2], otherPoints[3]) ||
      mthLineSegmentsIntersect(points[3], points[0], otherPoints[2], otherPoints[3]) ||
      mthLineSegmentsIntersect(points[0], points[1], otherPoints[3], otherPoints[0]) ||
      mthLineSegmentsIntersect(points[1], points[2], otherPoints[3], otherPoints[0]) ||
      mthLineSegmentsIntersect(points[2], points[3], otherPoints[3], otherPoints[0]) ||
      mthLineSegmentsIntersect(points[3], points[0], otherPoints[3], otherPoints[0])
  ) {
    return true;
  }

  return false;
}

SDL_Rect CRectangle::GetSDLRect() const
{
  SDL_Rect ret;
  ret.x = (int)x;
  ret.y = (int)y;
  ret.w = (int)w;
  ret.h = (int)h;
  return ret;
}

bool CRectangle::PointInPolygon(const Vector2f &p, const Vector2f* poly, int vertices)
{
  if(vertices < 3) {
    return false;
  }

  Vector2f p1, p2;
  bool inside = false;

  Vector2f oldPoint = poly[vertices-1];

  for(int i=0; i<vertices; i++) {
    const Vector2f &newPoint = poly[i];

    if(newPoint(1) > oldPoint(1)) {
      p1 = oldPoint;
      p2 = newPoint;
    } else {
      p1 = newPoint;
      p2 = oldPoint;
    }

    // The more I look at the if statement, the less I understand it.. wtf, Harry? ~ang
    if((newPoint(1) < p(1)) == (p(1) <= oldPoint(1))
      && ((long long)p(2) - (long long)p1(2)) * (long long)(p2(1) - p1(1))
       < ((long long)p2(2) - (long long)p1(2)) * (long long)(p(1) - p1(1))) {
      inside = !inside;
    }
    oldPoint = newPoint;
  }
  return inside;
}

MRAGPP_NAMESPACE_END;
