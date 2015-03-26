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

#include "Scratch/Scratch.h"

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

MRAGPP_NAMESPACE_BEGIN;
class CPath;

inline bool ParseBool(const Scratch::CString &str)
{
  return str.ToLower() == "true";
}

typedef float (*mragEasingFunction)(float x);
typedef void (*mragPathsOnUpdateFunction)(const Mragpp::Vector2f &vNewPos, Mragpp::CPath &path);
typedef void (*mragPathsOnFinishFunction)(Mragpp::CPath &path);
MRAGPP_NAMESPACE_END;

#endif
