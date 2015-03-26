#ifndef MRAGPP_WINDOW_H_INCLUDED
#define MRAGPP_WINDOW_H_INCLUDED

#include "StdH.h"

struct SDL_Window;

MRAGPP_NAMESPACE_BEGIN;

class MRAGPP_EXPORT CWindow
{
private:
  SDL_Window* win_pWindow;

public:
  CWindow();
  CWindow(SDL_Window* pWindow);
  ~CWindow();

  void Create(Scratch::CString strTitle, int width, int height, ULONG ulFlags);
  void Destroy();

  void SetTitle(const Scratch::CString &strTitle);

  operator SDL_Window*();
};

MRAGPP_NAMESPACE_END;

#endif
