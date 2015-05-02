#include "StdH.h"
#include "Window.h"

#include <SDL.h>
#include <GL/gl.h>

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

void CWindow::Create(Scratch::CString strTitle, int width, int height, ULONG ulFlags)
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

  win_pWindow = SDL_CreateWindow(strTitle, iX, iY, width, height, SDL_WINDOW_SHOWN | ulFlags);

  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
  glEnable(GL_MULTISAMPLE);

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

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

void CWindow::SetTitle(const Scratch::CString &strTitle)
{
  SDL_SetWindowTitle(win_pWindow, strTitle);
}

CWindow::operator SDL_Window*()
{
  return win_pWindow;
}

MRAGPP_NAMESPACE_END;
