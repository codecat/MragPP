#ifndef MRAGPP_VECTOR_CPP_INCLUDED
#define MRAGPP_VECTOR_CPP_INCLUDED

#include "StdH.h"
#include "Vector.h"

#include <cmath>

MRAGPP_NAMESPACE_BEGIN;

template<int N, class T>
Vector<N,T>::Vector()
{
  for(int i=0; i<N; i++) {
    vals[i] = T(0);
  }
}

template<int N, class T>
Vector<N,T>::Vector(const Vector<N,T> &copy)
{
  for(int i=0; i<N; i++) {
    vals[i] = copy.vals[i];
  }
}

template<int N, class T>
Vector<N,T>::Vector(T x, T y)
{
  ASSERT(N==2);
  vals[0] = x;
  vals[1] = y;
}

template<int N, class T>
Vector<N,T>::Vector(T x, T y, T z)
{
  ASSERT(N==3);
  vals[0] = x;
  vals[1] = y;
  vals[2] = z;
}

template<int N, class T>
Vector<N,T>::Vector(T x, T y, T z, T w)
{
  ASSERT(N==4);
  vals[0] = x;
  vals[1] = y;
  vals[2] = z;
  vals[3] = w;
}

template<int N, class T>
inline T Vector<N,T>::Length()
{
  double sum = 0;
  for(int i=0; i<N; i++) {
    T v = vals[i];
    sum += (v*v);
  }
  return (T)sqrt(sum);
}

template<int N, class T>
inline void Vector<N,T>::Normalize()
{
  *this /= Length();
}

template<int N, class T>
inline void Vector<N,T>::Clear()
{
  for(int i=0; i<N; i++) {
    vals[i] = 0;
  }
}

template<int N, class T>
inline Vector<N,T> Vector<N,T>::Cross(const Vector<N,T> &other) const
{
  ASSERT(N==3);
  Vector<N,T> ret;
  ret.vals[0] = vals[1] * other.vals[2] - vals[2] * other.vals[1];
  ret.vals[1] = vals[2] * other.vals[0] - vals[0] * other.vals[2];
  ret.vals[2] = vals[0] * other.vals[1] - vals[1] * other.vals[0];
  return ret;
}

/************************************************
 * Operators: Vector + Vector                   *
 ************************************************/
template<int N, class T>
inline Vector<N,T> Vector<N,T>::operator +(const Vector<N,T> &vRhs) const
{
  Vector<N,T> ret(*this);
  for(int i=0; i<N; i++) {
    ret.vals[i] += vRhs.vals[i];
  }
  return ret;
}

template<int N, class T>
inline Vector<N,T> Vector<N,T>::operator -(const Vector<N,T> &vRhs) const
{
  Vector<N,T> ret(*this);
  for(int i=0; i<N; i++) {
    ret.vals[i] -= vRhs.vals[i];
  }
  return ret;
}

template<int N, class T>
inline Vector<N,T> Vector<N,T>::operator *(const Vector<N,T> &vRhs) const
{
  Vector<N,T> ret(*this);
  for(int i=0; i<N; i++) {
    ret.vals[i] *= vRhs.vals[i];
  }
  return ret;
}

template<int N, class T>
inline Vector<N,T> Vector<N,T>::operator /(const Vector<N,T> &vRhs) const
{
  Vector<N,T> ret(*this);
  for(int i=0; i<N; i++) {
    ret.vals[i] /= vRhs.vals[i];
  }
  return ret;
}

/************************************************
 * Operators: Vector + T                        *
 ************************************************/

template<int N, class T>
inline Vector<N,T> Vector<N,T>::operator +(T tRhs) const
{
  Vector<N,T> ret(*this);
  for(int i=0; i<N; i++) {
    ret.vals[i] += tRhs;
  }
  return ret;
}

template<int N, class T>
inline Vector<N,T> Vector<N,T>::operator -(T tRhs) const
{
  Vector<N,T> ret(*this);
  for(int i=0; i<N; i++) {
    ret.vals[i] -= tRhs;
  }
  return ret;
}

template<int N, class T>
inline Vector<N,T> Vector<N,T>::operator *(T tRhs) const
{
  Vector<N,T> ret(*this);
  for(int i=0; i<N; i++) {
    ret.vals[i] *= tRhs;
  }
  return ret;
}

template<int N, class T>
inline Vector<N,T> Vector<N,T>::operator /(T tRhs) const
{
  Vector<N,T> ret(*this);
  for(int i=0; i<N; i++) {
    ret.vals[i] /= tRhs;
  }
  return ret;
}

/************************************************
 * Operators: Vector += Vector                  *
 ************************************************/
template<int N, class T>
inline Vector<N,T> &Vector<N,T>::operator +=(const Vector<N,T> &vRhs)
{
  for(int i=0; i<N; i++) {
    vals[i] += vRhs.vals[i];
  }
  return *this;
}

template<int N, class T>
inline Vector<N,T> &Vector<N,T>::operator -=(const Vector<N,T> &vRhs)
{
  for(int i=0; i<N; i++) {
    vals[i] -= vRhs.vals[i];
  }
  return *this;
}

template<int N, class T>
inline Vector<N,T> &Vector<N,T>::operator *=(const Vector<N,T> &vRhs)
{
  for(int i=0; i<N; i++) {
    vals[i] *= vRhs.vals[i];
  }
  return *this;
}

template<int N, class T>
inline Vector<N,T> &Vector<N,T>::operator /=(const Vector<N,T> &vRhs)
{
  for(int i=0; i<N; i++) {
    vals[i] /= vRhs.vals[i];
  }
  return *this;
}

/************************************************
 * Operators: Vector == Vector                  *
 ************************************************/
template<int N, class T>
inline bool operator==(const Vector<N,T> &vLhs, const Vector<N,T> &vRhs)
{
  for(int i=0; i<N; i++) {
    if(vLhs.vals[i] != vRhs.vals[i]) {
      return false;
    }
  }
  return true;
}

template<int N, class T>
inline bool operator!=(const Vector<N,T> &vLhs, const Vector<N,T> &vRhs)
{
  for(int i=0; i<N; i++) {
    if(vLhs.vals[i] != vRhs.vals[i]) {
      return true;
    }
  }
  return false;
}

/************************************************
 * Operators: Vector += T                       *
 ************************************************/
template<int N, class T>
inline Vector<N,T> &Vector<N,T>::operator +=(T tRhs)
{
  for(int i=0; i<N; i++) {
    vals[i] += tRhs;
  }
  return *this;
}

template<int N, class T>
inline Vector<N,T> &Vector<N,T>::operator -=(T tRhs)
{
  for(int i=0; i<N; i++) {
    vals[i] -= tRhs;
  }
  return *this;
}

template<int N, class T>
inline Vector<N,T> &Vector<N,T>::operator *=(T tRhs)
{
  for(int i=0; i<N; i++) {
    vals[i] *= tRhs;
  }
  return *this;
}

template<int N, class T>
inline Vector<N,T> &Vector<N,T>::operator /=(T tRhs)
{
  for(int i=0; i<N; i++) {
    vals[i] /= tRhs;
  }
  return *this;
}

template<int N, class T>
template<int NN, typename TT> inline Vector<NN,TT> Vector<N,T>::GetAs()
{
  Vector<NN,TT> ret;
  for(int i=0; i<NN; i++) {
    if(i < N) {
      ret.vals[i] = TT(vals[i]);
    }
  }
  return ret;
}

template<int N, class T>
template<int NN, typename TT> inline Vector<NN,TT> Vector<N,T>::GetAs() const
{
  Vector<NN,TT> ret;
  for(int i=0; i<NN; i++) {
    if(i < N) {
      ret.vals[i] = TT(vals[i]);
    }
  }
  return ret;
}

template<int N, class T>
inline T &Vector<N,T>::operator()(int index)
{
  return vals[index-1];
}

template<int N, class T>
inline const T &Vector<N,T>::operator()(int index) const
{
  return vals[index-1];
}

MRAGPP_NAMESPACE_END;

#endif
