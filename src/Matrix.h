#ifndef MRAGPP_MATRIX_H_INCLUDED
#define MRAGPP_MATRIX_H_INCLUDED

#include "StdH.h"

MRAGPP_NAMESPACE_BEGIN;

#define IDENTITY_MATRIX (CMatrix(\
  1, 0, 0, 0,\
  0, 1, 0, 0,\
  0, 0, 1, 0,\
  0, 0, 0, 1))

class MRAGPP_EXPORT CMatrix
{
private:
  float m11, m12, m13, m14;
  float m21, m22, m23, m24;
  float m31, m32, m33, m34;
  float m41, m42, m43, m44;

public:
  static CMatrix CreateRotationX(float rotation); // rotation in radians
  static CMatrix CreateRotationY(float rotation); // rotation in radians
  static CMatrix CreateRotationZ(float rotation); // rotation in radians
  static CMatrix CreateScale(float scale);
  static CMatrix CreateScale(float scaleX, float scaleY, float scaleZ);
  static CMatrix CreateTranslation(float x, float y, float z);
  static CMatrix CreateLookAt(float eyex, float eyey, float eyez, float targetx, float targety, float targetz, float upx, float upy, float upz);
  static CMatrix CreateLookAt(const Vector3f &eyePos, const Vector3f &targetPos, const Vector3f &upPos);
  static CMatrix CreatePerspective(float fovy, float aspect, float zNear, float zFar);

  CMatrix();
  CMatrix(
    float m11, float m12, float m13, float m14,
    float m21, float m22, float m23, float m24,
    float m31, float m32, float m33, float m34,
    float m41, float m42, float m43, float m44);
  CMatrix(float values);

  void DebugPrint();
  void ToFloatArray(float* pArray); // requires array size of at least (typeof(float)*16)

  Vector3f Transform(float x, float y, float z) const;
  Vector3f Transform(const Vector3f &input) const;

  Vector2f Transform(float x, float y) const;
  Vector2f Transform(const Vector2f &input) const;

  void SetTransform(int &x, int &y) const;
  void SetTransform(float &x, float &y) const;
  void SetTransform(Vector2f &input) const;

  CMatrix operator*(const CMatrix &other) const;
};

MRAGPP_NAMESPACE_END;

#endif
