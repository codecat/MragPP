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

	SetContext();
}

void CWindow::SetContext()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	win_pContext = SDL_GL_CreateContext(win_pWindow);
	printf("GLSL version 1: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	if(win_pContext == 0) {
		printf("SDL context creation error: '%s'\n", SDL_GetError());
		return;
	}

	static bool _bInitializedGlew = false;
	if(!_bInitializedGlew) {
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if(err != GLEW_OK) {
			printf("Glew initialization error: %d\n", err);
		}
		_bInitializedGlew = true;
	}

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	glEnable(GL_MULTISAMPLE);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	printf("GLSL version 2: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void CWindow::Destroy()
{
  if(win_pWindow == 0) {
    return;
  }

  SDL_DestroyWindow(win_pWindow);
  win_pWindow = 0;

	SDL_GL_DeleteContext(win_pContext);
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
