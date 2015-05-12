#ifndef MRAGPP_EASING_H_INCLUDED
#define MRAGPP_EASING_H_INCLUDED

#include "StdH.h"

MRAGPP_NAMESPACE_BEGIN;

class MRAGPP_EXPORT Easing
{
public:
  static float Linear(float x);

  static float InQuad(float x);
  static float OutQuad(float x);
  static float InOutQuad(float x);

  static float InCubic(float x);
  static float OutCubic(float x);
  static float InOutCubic(float x);

  static float InQuart(float x);
  static float OutQuart(float x);
  static float InOutQuart(float x);

  static float InQuint(float x);
  static float OutQuint(float x);
  static float InOutQuint(float x);

  static float InSine(float x);
  static float OutSine(float x);
  static float InOutSine(float x);

  static float InExpo(float x);
  static float OutExpo(float x);
  static float InOutExpo(float x);

  static float InCircle(float x);
  static float OutCircle(float x);
  static float InOutCircle(float x);

  static float InElastic(float x);
  static float OutElastic(float x);
  static float InOutElastic(float x);

  static float InBack(float x);
  static float OutBack(float x);
  static float InOutBack(float x);

  static float InBounce(float x);
  static float OutBounce(float x);
  static float InOutBounce(float x);
};

MRAGPP_NAMESPACE_END;

#endif
