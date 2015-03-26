#ifndef MRAGPP_SPECIALMATH_H_INCLUDED
#define MRAGPP_SPECIALMATH_H_INCLUDED

#include "StdH.h"
#include "Vector.h"

#define MATH_PI (3.14159265358f)
#define MATH_PI_2 (MATH_PI/2)

MRAGPP_NAMESPACE_BEGIN;

template<typename T>
inline T mthToRadians(T deg)
{
  return deg * T(MATH_PI / 180);
}

template<typename T>
inline T mthToDegrees(T rad)
{
  return rad * T(180 / MATH_PI);
}

template<class T>
inline T mthLerp(T a, T b, float x)
{
  return T(a + (b - a) * x);
}

template<class T>
inline int mthRound(T x)
{
  return (x > 0) ? (int)(x + T(0.5f)) : (int)(x - T(0.5f));
}

template<class T>
inline T mthMin(T a, T b)
{
  return (a > b ? b : a);
}

template<class T>
inline T mthMax(T a, T b)
{
  return (a > b ? a : b);
}

template<class T>
inline T mthClamp(T x, T min, T max)
{
  return (x < min ? min : (x > max ? max : x));
}

template<class T>
inline T mthAbs(T x)
{
  return (x < 0 ? -x : x);
}

inline float mthFloorF(float x)
{
  return (float)floor((long double)x);
}

inline float mthCeilF(float x)
{
  return (float)ceil((long double)x);
}

inline float mthRndf()
{
  return (float)rand() / (float)RAND_MAX;
}

inline double mthRndd()
{
  return (double)rand() / (double)RAND_MAX;
}

inline Vector2f IntersectionPoint(const Vector2f &a1, const Vector2f &a2, const Vector2f &b1, const Vector2f &b2)
{
  float x1, x2, x3, x4, y1, y2, y3, y4;
  x1 = a1(1); y1 = a1(2);
  x2 = a2(1); y2 = a2(2);
  x3 = b1(1); y3 = b1(2);
  x4 = b2(1); y4 = b2(2);

  // from https://en.wikipedia.org/wiki/Line-line_intersection
  return Vector2f(
    ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)),
    ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)));
}

inline bool mthLineSegmentsIntersect(const Vector2f &a1, const Vector2f &a2, const Vector2f &b1, const Vector2f &b2)
{
  Vector2f intersectionPoint = IntersectionPoint(a1, a2, b1, b2);

  if(intersectionPoint(1) > mthMin(a1(1), a2(1)) &&
     intersectionPoint(1) < mthMax(a1(1), a2(1)) &&
     intersectionPoint(2) > mthMin(a1(2), a2(2)) &&
     intersectionPoint(2) < mthMax(a1(2), a2(2)) &&

     intersectionPoint(1) > mthMin(b1(1), b2(1)) &&
     intersectionPoint(1) > mthMin(b1(1), b2(1)) &&
     intersectionPoint(1) > mthMin(b1(1), b2(1)) &&
     intersectionPoint(1) > mthMin(b1(1), b2(1))
  ) {
    return true;
  }

  return false;
}

inline bool mthLineSegmentsIntersectAt(Vector2f &vIntersectionPoint, const Vector2f &a1, const Vector2f &a2, const Vector2f &b1, const Vector2f &b2)
{
  Vector2f intersectionPoint = IntersectionPoint(a1, a2, b1, b2);

  if(intersectionPoint(1) > mthMin(a1(1), a2(1)) &&
     intersectionPoint(1) < mthMax(a1(1), a2(1)) &&
     intersectionPoint(2) > mthMin(a1(2), a2(2)) &&
     intersectionPoint(2) < mthMax(a1(2), a2(2)) &&

     intersectionPoint(1) > mthMin(b1(1), b2(1)) &&
     intersectionPoint(1) > mthMin(b1(1), b2(1)) &&
     intersectionPoint(1) > mthMin(b1(1), b2(1)) &&
     intersectionPoint(1) > mthMin(b1(1), b2(1))
  ) {
    vIntersectionPoint = intersectionPoint;
    return true;
  }

  return false;
}

MRAGPP_NAMESPACE_END;

#endif
