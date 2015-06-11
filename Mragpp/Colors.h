#ifndef MRAGPP_COLORS_H_INCLUDED
#define MRAGPP_COLORS_H_INCLUDED

#include "StdH.h"
#include "Easing.h"

typedef unsigned char COLOR_VALUE;
typedef unsigned long COLOR;

#define MRAG_ALPHA_OPAQUE       0xFF
#define MRAG_ALPHA_TRANSPARANT  0x80
#define MRAG_ALPHA_INVISIBLE    0x00

#define MRAG_COLOR_RGBA(r, g, b, a) ((COLOR)(((r) << 24) | ((g) << 16) | ((b) << 8) | (a)))
#define MRAG_COLOR_RGB(r, g, b) MRAG_COLOR_RGBA((r), (g), (b), 255)
#define MRAG_COLOR_RGB_SCALED(r, g, b, s) MRAG_COLOR_RGB((int)((r) * (s)), (int)((g) * (s)), (int)((b) * (s)))
#define MRAG_COLOR_EXPLODE_R(c) ((COLOR_VALUE)(((c) & 0xFF000000) >> 24))
#define MRAG_COLOR_EXPLODE_G(c) ((COLOR_VALUE)(((c) & 0x00FF0000) >> 16))
#define MRAG_COLOR_EXPLODE_B(c) ((COLOR_VALUE)(((c) & 0x0000FF00) >>  8))
#define MRAG_COLOR_EXPLODE_A(c) ((COLOR_VALUE) ((c) & 0x000000FF)       )
#define MRAG_COLOR_EXPLODE_RGBA(c, r, g, b, a) \
  r = MRAG_COLOR_EXPLODE_R(c); \
  g = MRAG_COLOR_EXPLODE_G(c); \
  b = MRAG_COLOR_EXPLODE_B(c); \
  a = MRAG_COLOR_EXPLODE_A(c);
#define MRAG_COLOR_EXPLODE_RGB(c, r, g, b) \
  r = MRAG_COLOR_EXPLODE_R(c); \
  g = MRAG_COLOR_EXPLODE_G(c); \
  b = MRAG_COLOR_EXPLODE_B(c);

#define COL_BLACK       0x00000000
#define COL_WHITE       0xFFFFFF00

#define COL_RED         0xFF000000
#define COL_GREEN       0x00FF0000
#define COL_BLUE        0x0000FF00

#define COL_YELLOW      0xFFFF0000
#define COL_PINK        0xFF00FF00
#define COL_CYAN        0x00FFFF00

#define COL_ORANGE      0xFF800000

#define COL_NIMBLE      0xFFF7D700
#define COL_NIMBLE_TIP  0xFFBD9300

#define COL_RD_BLUE     0x9EDBF900
#define COL_RD_MANE1    0xEE414400
#define COL_RD_MANE2    0xF3703300
#define COL_RD_MANE3    0xFDF6AF00
#define COL_RD_MANE4    0x62BC4D00
#define COL_RD_MANE5    0x1E98D300
#define COL_RD_MANE6    0x672F8900

MRAGPP_NAMESPACE_BEGIN;

inline COLOR MRAGPP_EXPORT LerpColor(COLOR a, COLOR b, float x)
{
  COLOR_VALUE ar, ag, ab, aa;
  COLOR_VALUE br, bg, bb, ba;

  MRAG_COLOR_EXPLODE_RGBA(a, ar, ag, ab, aa);
  MRAG_COLOR_EXPLODE_RGBA(b, br, bg, bb, ba);

  return MRAG_COLOR_RGBA(
    mthLerp(ar, br, x),
    mthLerp(ag, bg, x),
    mthLerp(ab, bb, x),
    mthLerp(aa, ba, x));
}

inline COLOR MRAGPP_EXPORT RainbowDash()
{
  static int iMane = 1;
  static float fLerp = 0.0f;

  if(fLerp >= 1.0f) {
    if(++iMane > 6) {
      iMane = 1;
    }
    fLerp = 0.0f;
  } else {
    fLerp += 0.025f;
  }

  COLOR a = 0, b = 0;

  if(iMane == 1) { a = COL_RD_MANE1; b = COL_RD_MANE2; }
  if(iMane == 2) { a = COL_RD_MANE2; b = COL_RD_MANE3; }
  if(iMane == 3) { a = COL_RD_MANE3; b = COL_RD_MANE4; }
  if(iMane == 4) { a = COL_RD_MANE4; b = COL_RD_MANE5; }
  if(iMane == 5) { a = COL_RD_MANE5; b = COL_RD_MANE6; }
  if(iMane == 6) { a = COL_RD_MANE6; b = COL_RD_MANE1; }

  return LerpColor(a, b, Easing::InOutQuad(fLerp));
}

inline COLOR MRAGPP_EXPORT HexToColor(const Scratch::String &str)
{
  unsigned char R, G, B, A = 0xFF;
  int iLen = strlen(str);
  if(iLen >= 6) {
    R = (unsigned char)strtol(str.SubString(0, 2), NULL, 16);
    G = (unsigned char)strtol(str.SubString(2, 2), NULL, 16);
    B = (unsigned char)strtol(str.SubString(4, 2), NULL, 16);
    if(iLen == 8) {
      A = (unsigned char)strtol(str.SubString(6, 2), NULL, 16);
    }
  } else if(iLen >= 3) {
    R = (unsigned char)strtol(str.SubString(0, 1), NULL, 16) * 0x11;
    G = (unsigned char)strtol(str.SubString(1, 1), NULL, 16) * 0x11;
    B = (unsigned char)strtol(str.SubString(2, 1), NULL, 16) * 0x11;
    if(iLen == 4) {
      A = (unsigned char)strtol(str.SubString(3, 1), NULL, 16) * 0x11;
    }
  } else {
    ASSERT(FALSE);
  }
  return MRAG_COLOR_RGBA(R, G, B, A);
}

struct rgb
{
  unsigned char r; // byte (0-255)
  unsigned char g; // byte (0-255)
  unsigned char b; // byte (0-255)
};

struct hsv
{
  short h; // degrees (0-360)
  unsigned char s; // percent (0-100)
  unsigned char v; // percent (0-100)
};

inline rgb MRAGPP_EXPORT col2rgb(COLOR col);
inline hsv MRAGPP_EXPORT col2hsv(COLOR col);
inline COLOR MRAGPP_EXPORT rgb2col(const rgb &rgb);
inline COLOR MRAGPP_EXPORT hsv2col(const hsv &hsv);
inline hsv MRAGPP_EXPORT rgb2hsv(const rgb &rgb);
inline rgb MRAGPP_EXPORT hsv2rgb(const hsv &hsv);

inline COLOR MRAGPP_EXPORT colMod(COLOR col, float fModH, float fModS, float fModV);

MRAGPP_NAMESPACE_END;

#endif
