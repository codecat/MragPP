#include "StdH.h"
#include "Colors.h"

MRAGPP_NAMESPACE_BEGIN;

#define MAX3(x, y, z) (x > y ? (x > z ? x : z) : (y > z ? y : z))
#define MIN3(x, y, z) (x < y ? (x < z ? x : z) : (y < z ? y : z))

inline rgb col2rgb(COLOR col)
{
  rgb rgb;
  rgb.r = MRAG_COLOR_EXPLODE_R(col);
  rgb.g = MRAG_COLOR_EXPLODE_G(col);
  rgb.b = MRAG_COLOR_EXPLODE_B(col);
  return rgb;
}

inline hsv col2hsv(COLOR col)
{
  return rgb2hsv(col2rgb(col));
}

inline COLOR rgb2col(const rgb &rgb)
{
  return MRAG_COLOR_RGB(rgb.r, rgb.g, rgb.b);
}

inline COLOR hsv2col(const hsv &hsv)
{
  return rgb2col(hsv2rgb(hsv));
}

inline hsv rgb2hsv(const rgb &rgb)
{
  float h, s = 0;
  float r = rgb.r / 255.0f;
  float g = rgb.g / 255.0f;
  float b = rgb.b / 255.0f;
  float M = MAX3(r, g, b);
  float c = M - MIN3(r, g, b);
  if     (c == 0) h = 0;
  else if(M == r) h = fmod(((g - b) / c), 6) * 60;
  else if(M == g) h = ((b - r) / c + 2) * 60;
  else h = ((r - g) / c + 4) * 60;
  if(h < 0.0f) h += 360;
  if(c != 0) s = c / M;
  hsv hsv;
  hsv.h = (short)h;
  hsv.s = (unsigned char)(s * 100.0f);
  hsv.v = (unsigned char)(M * 100.0f);
  return hsv;
}

inline rgb hsv2rgb(const hsv &hsv)
{
  float h = mthClamp((float)hsv.h, 0.0f, 359.0f);
  float s = mthClamp(hsv.s / 100.0f, 0.0f, 1.0f);
  float v = mthClamp(hsv.v / 100.0f, 0.0f, 1.0f);
  float c = v * s;
  float x = c * (1 - abs(fmod(h / 60.0f, 2) - 1));
  float r = 0, g = 0, b = 0;
  if     (h >=   0 && h <  60) { r = c; g = x; }
  else if(h >=  60 && h < 120) { r = x; g = c; }
  else if(h >= 120 && h < 180) { g = c; b = x; }
  else if(h >= 180 && h < 240) { g = x; b = c; }
  else if(h >= 240 && h < 300) { r = x; b = c; }
  else if(h >= 300 && h < 360) { r = c; b = x; }
  rgb rgb;
  rgb.r = (unsigned char)((r + (v - c)) * 255);
  rgb.g = (unsigned char)((g + (v - c)) * 255);
  rgb.b = (unsigned char)((b + (v - c)) * 255);
  return rgb;
}

inline COLOR colMod(COLOR col, float fModH, float fModS, float fModV)
{
  hsv hsv = col2hsv(col);
  hsv.h = (int)(hsv.h * fModH);
  hsv.s = (int)(hsv.s * fModS);
  hsv.v = (int)(hsv.v * fModV);
  return hsv2col(hsv);
}

MRAGPP_NAMESPACE_END;
