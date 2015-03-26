#include "StdH.h"
#include "Engine.h"

#include <cstdio>
#include <ctime>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

MRAGPP_NAMESPACE_BEGIN;

int g_iGamesRunning = 0;

void InitializeEngine()
{
  if(g_iGamesRunning > 0) {
    return;
  }

  srand((unsigned int)time(NULL));

  // NOTE: Don't initialize these: SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER
  //       They sometimes take a LONG time to load, possibly due to unsupported controllers? (Xbox One beta driver)
  //       Due to this, we should only initialize those if necessary.
  //TODO: Make some way to initialize gamepad support - though making an Xinput implementation ourselves might be better
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_EVENTS) == -1) {
    printf("SDL initialization error: '%s'\n", SDL_GetError());
    return;
  }

  if(TTF_Init() == -1) {
    printf("TTF initialization error: '%s'\n", TTF_GetError());
    return;
  }

  g_iGamesRunning++;
}

void EndEngine()
{
  g_iGamesRunning--;

  if(g_iGamesRunning < 0) {
    throw "There are already no games running.";
  }

  if(g_iGamesRunning == 0) {
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    printf("SDL completely died\n");
  }
}

MRAGPP_NAMESPACE_END;
