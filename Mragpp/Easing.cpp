#include "StdH.h"
#include "Easing.h"

MRAGPP_NAMESPACE_BEGIN;

float Easing::Linear(float x)
{
  return x;
}

float Easing::InQuad(float x)
{
  return x * x;
}

float Easing::OutQuad(float x)
{
  return -x * (x - 2);
}

float Easing::InOutQuad(float x)
{
  if ((x /= 0.5f) < 1) return 0.5f * x * x;
  x--;
  return -0.5f * (x * (x - 2) - 1);
}

float Easing::InCubic(float x)
{
  return x * x * x;
}

float Easing::OutCubic(float x)
{
  x -= 1;
  return x * x * x + 1;
}

float Easing::InOutCubic(float x)
{
  if ((x /= 0.5f) < 1) return 0.5f * x * x * x;
  x -= 2;
  return 0.5f * (x * x * x + 2);
}

float Easing::InQuart(float x)
{
  return x * x * x * x;
}

float Easing::OutQuart(float x)
{
  x -= 1;
  return -(x * x * x * x - 1);
}

float Easing::InOutQuart(float x)
{
  x /= 0.5f;
  if (x < 1) return 0.5f * x * x * x * x;
  x -= 2;
  return -0.5f * (x * x * x * x - 2);
}

float Easing::InQuint(float x)
{
  return x * x * x * x * x;
}

float Easing::OutQuint(float x)
{
  x -= 1;
  return x * x * x * x * x + 1;
}

float Easing::InOutQuint(float x)
{
  x /= 0.5f;
  if (x < 1) return 0.5f * x * x * x * x * x;
  x -= 2;
  return 0.5f * (x * x * x * x * x + 2);
}

float Easing::InSine(float x)
{
  return -(float)sin(x * (MATH_PI / 2)) + 1;
}

float Easing::OutSine(float x)
{
  return (float)sin(x * (MATH_PI / 2));
}

float Easing::InOutSine(float x)
{
  return -0.5f * ((float)cos(MATH_PI * x) - 1);
}

float Easing::InExpo(float x)
{
  return (x == 0) ? 0 : ((float)cos(MATH_PI * x) - 1);
}

float Easing::OutExpo(float x)
{
  return (x == 1) ? 1 : -(float)pow(2, 10 * (x - 1));
}

float Easing::InOutExpo(float x)
{
  if (x == 0) return 0;
  if (x == 1) return 1;
  x /= 0.5f;
  if (x < 1) return 0.5f * (float)pow(2, 10 * (x - 1));
  return 0.5f * (-(float)pow(2, -10 * --x) + 2);
}

float Easing::InCircle(float x)
{
  return -((float)sqrt(1 - x * x) - 1);
}

float Easing::OutCircle(float x)
{
  x -= 1;
  return (float)sqrt(1 - x * x);
}

float Easing::InOutCircle(float x)
{
  x /= 0.5f;
  if (x < 1) return -0.5f * ((float)sqrt(1 - x * x) - 1);
  x -= 2;
  return 0.5f * ((float)sqrt(1 - x * x) + 1);
}

float Easing::InElastic(float x)
{
  float s = 0.075f;
  if (x == 0) return 0;
  if (x == 1) return 1;
  x -= 1;
  return -((float)pow(2, 10 * x) * (float)sin((x - s) * (2 * MATH_PI) / 0.3f));
}

float Easing::OutElastic(float x)
{
  float s = 0.075f;
  if (x == 0) return 0;
  if (x == 1) return 1;
  return (float)pow(2, -10 * x) * (float)sin((x - s) * (2 * MATH_PI) / 0.3f) + 1;
}

float Easing::InOutElastic(float x)
{
  float s = 0.1125f;
  if (x == 0) return 0;
  x /= 0.5f;
  if (x == 2) return 1;
  if (x < 1) {
    x -= 1;
    return -0.5f * ((float)pow(2, 10 * x) * (float)sin((x - s) * (2 * MATH_PI) / 0.45f));
  }
  x -= 1;
  return (float)pow(2, -10 * x) * (float)sin((x - s) * (2 * MATH_PI) / 0.45f) * 0.5f + 1;
}

float Easing::InBack(float x)
{
  float s = 1.70158f;
  return x * x * ((s + 1) * x - s);
}

float Easing::OutBack(float x)
{
  float s = 1.70158f;
  x -= 1;
  return x * x * ((s + 1) * x + s) + 1;
}

float Easing::InOutBack(float x)
{
  float s = 1.70158f;
  x /= 0.5f;
  if (x < 1) {
    s *= 1.525f;
    return 0.5f * (x * x * ((s + 1) * x - s));
  }
  s *= 1.525f;
  x -= 2;
  return 0.5f * (x * x * ((s + 1) * x + s) + 2);
}

float Easing::InBounce(float x)
{
  return 1 - OutBounce(1 - x);
}

float Easing::OutBounce(float x)
{
  if(x < (1 / 2.75)) {
    return 7.5625f * x * x;
  } else if(x < (2 / 2.75)) {
    x -= (1.5f / 2.75f);
    return 7.5625f * x * x + 0.75f;
  } else if(x < (2.5 / 2.75)) {
    x -= (2.25f / 2.75f);
    return 7.5625f * x * x + 0.9375f;
  } else {
    x -= (2.625f / 2.75f);
    return 7.5625f * x * x + 0.984375f;
  }
}

float Easing::InOutBounce(float x)
{
  if (x < 0.5f) return InBounce(x * 2) * 0.5f;
  return OutBounce(x * 2 - 1) * 0.5f + 0.5f;
}

MRAGPP_NAMESPACE_END;
