#include "StdH.h"
#include "Window.h"

#include <SDL.h>
#include <GL/glew.h>

MRAGPP_NAMESPACE_BEGIN;

CWindow::CWindow()
{
  win_pWindow = 0;
}

CWindow::CWindow(SDL_Window* pWindow)
{
  win_pWindow = pWindow;
}

CWindow::~CWindow()
{
  Destroy();
}

void CWindow::Create(Scratch::String strTitle, int width, int height, ULONG ulFlags)
{
#if WINDOWS
  int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
  int iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);

  int iX = iScreenWidth / 2 - width / 2;
  int iY = iScreenHeight / 2 - height / 2;
#else
  int iX = 70;
  int iY = 50;
#endif

  win_pWindow = SDL_CreateWindow(strTitle, iX, iY, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | ulFlags);

  if(win_pWindow == 0) {
    printf("SDL window creation error: '%s'\n", SDL_GetError());
    return;
  }
}

void CWindow::Destroy()
{
  if(win_pWindow == 0) {
    return;
  }

  SDL_DestroyWindow(win_pWindow);
  win_pWindow = 0;
}

void CWindow::SetTitle(const Scratch::String &strTitle)
{
  SDL_SetWindowTitle(win_pWindow, strTitle);
}

CWindow::operator SDL_Window*()
{
  return win_pWindow;
}

MRAGPP_NAMESPACE_END;
