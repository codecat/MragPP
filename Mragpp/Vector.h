#ifndef MRAGPP_VECTOR_H_INCLUDED
#define MRAGPP_VECTOR_H_INCLUDED

#include "StdH.h"

MRAGPP_NAMESPACE_BEGIN;

template<int N, class T>
struct MRAGPP_EXPORT Vector
{
  T vals[N];

  Vector();
  Vector(const Vector<N,T> &copy);
  Vector(T x, T y); // for N=2
  Vector(T x, T y, T z); // for N=3
  Vector(T x, T y, T z, T w); // for N=4

  inline T Length();
  inline void Normalize();
  inline void Clear();

  inline Vector<N,T> Cross(const Vector<N,T> &other) const;

  inline Vector<N,T> operator +(const Vector<N,T> &vRhs) const;
  inline Vector<N,T> operator -(const Vector<N,T> &vRhs) const;
  inline Vector<N,T> operator *(const Vector<N,T> &vRhs) const;
  inline Vector<N,T> operator /(const Vector<N,T> &vRhs) const;

  inline Vector<N,T> operator +(T tRhs) const;
  inline Vector<N,T> operator -(T tRhs) const;
  inline Vector<N,T> operator *(T tRhs) const;
  inline Vector<N,T> operator /(T tRhs) const;

  inline Vector<N,T> &operator +=(const Vector<N,T> &vRhs);
  inline Vector<N,T> &operator -=(const Vector<N,T> &vRhs);
  inline Vector<N,T> &operator *=(const Vector<N,T> &vRhs);
  inline Vector<N,T> &operator /=(const Vector<N,T> &vRhs);

  inline Vector<N,T> &operator +=(T tRhs);
  inline Vector<N,T> &operator -=(T tRhs);
  inline Vector<N,T> &operator *=(T tRhs);
  inline Vector<N,T> &operator /=(T tRhs);

  template<int NN, typename TT> inline Vector<NN,TT> GetAs();
  template<int NN, typename TT> inline Vector<NN,TT> GetAs() const;

  inline       T &operator()(int index);
  inline const T &operator()(int index) const;
};

template<int N, class T>
inline bool operator==(const Vector<N,T> &vLhs, const Vector<N,T> &vRhs);
template<int N, class T>
inline bool operator!=(const Vector<N,T> &vLhs, const Vector<N,T> &vRhs);

typedef Vector<2, int> Vector2i;
typedef Vector<2, float> Vector2f;
typedef Vector<2, double> Vector2d;

typedef Vector<3, int> Vector3i;
typedef Vector<3, float> Vector3f;
typedef Vector<3, double> Vector3d;

typedef Vector<4, int> Vector4i;
typedef Vector<4, float> Vector4f;
typedef Vector<4, double> Vector4d;

inline Vector2f ParseVector2f(const Scratch::String &str)
{
  Scratch::StackArray<Scratch::String> parse;
  str.Split(",", parse, TRUE);
  return Vector2f((float)atof(parse[0]), (float)atof(parse[1]));
}

MRAGPP_NAMESPACE_END;

#include "Vector.cpp"

#endif
