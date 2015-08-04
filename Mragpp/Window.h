#ifndef MRAGPP_WINDOW_H_INCLUDED
#define MRAGPP_WINDOW_H_INCLUDED

#include "StdH.h"

struct SDL_Window;

MRAGPP_NAMESPACE_BEGIN;

class MRAGPP_EXPORT CWindow
{
private:
  SDL_Window* win_pWindow;
	void* win_pContext;

public:
  CWindow();
  CWindow(SDL_Window* pWindow);
  ~CWindow();

  void Create(Scratch::String strTitle, int width, int height, ULONG ulFlags);
	void SetContext();
  void Destroy();

  void SetTitle(const Scratch::String &strTitle);

  operator SDL_Window*();
};

MRAGPP_NAMESPACE_END;

#endif
