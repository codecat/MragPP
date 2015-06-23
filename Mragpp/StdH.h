#ifndef MRAGPP_STDH_H_INCLUDED
#define MRAGPP_STDH_H_INCLUDED

#include <cstdio>
#include <cstdlib>

#ifdef _MSC_VER
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#endif

#include <Scratch/Scratch.h>

#define MRAGPP_NAMESPACE_BEGIN namespace Mragpp {
#define MRAGPP_NAMESPACE_END }

#ifdef _MSC_VER
#define MRAGPP_EXPORT __declspec(dllexport)
#else
#define MRAGPP_EXPORT
#endif

//#include "Memory.h"

#include "SpecialMath.h"
#include "Colors.h"

#include <SDL2/SDL.h>
#ifndef _MSC_VER
#include <signal.h>

#ifdef ASSERT
#undef ASSERT
#endif
#define ASSERT(x) { \
  static UBYTE _ubWasHere = 0; \
  if(!_ubWasHere) { \
    if(!(x)) { \
      SDL_MessageBoxButtonData _mbbs[] = { \
        { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT | SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Ignore" }, \
        { 0, 1, "Abort" }, \
        { 0, 2, "Break" } \
      }; \
      Scratch::String _mbt; \
      _mbt.SetF("Assertion failed:\n\n%s:%d\n\n\"%s\"", __FILE__, __LINE__, #x); \
      SDL_MessageBoxData _mbd = { \
        SDL_MESSAGEBOX_WARNING, \
        NULL, \
        "Assertion failed", \
        _mbt, \
        3, _mbbs \
      }; \
      int _iButton = -1; \
      SDL_ShowMessageBox(&_mbd, &_iButton); \
      if(_iButton == 0) { \
        _ubWasHere = 1; \
      } else if(_iButton == 1) { \
        exit(1); \
      } else if(_iButton == 2) { \
        raise(SIGINT); \
      } \
    } \
  } \
}
#endif

MRAGPP_NAMESPACE_BEGIN;
class CPath;

inline bool ParseBool(const Scratch::String &str)
{
  return str.ToLower() == "true";
}

typedef float (*mragEasingFunction)(float x);
typedef void (*mragPathsOnUpdateFunction)(const Mragpp::Vector2f &vNewPos, Mragpp::CPath &path);
typedef void (*mragPathsOnFinishFunction)(Mragpp::CPath &path);
MRAGPP_NAMESPACE_END;

#endif
