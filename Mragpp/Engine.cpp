#include "StdH.h"
#include "Engine.h"

#include <cstdio>
#include <ctime>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

MRAGPP_NAMESPACE_BEGIN;

int g_iGamesRunning = 0;

void InitializeEngine()
{
  if(g_iGamesRunning > 0) {
    g_iGamesRunning++;
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

  int iMixerFlags = MIX_INIT_OGG | MIX_INIT_MP3;
  if(Mix_Init(iMixerFlags) != iMixerFlags) {
    printf("Warning: Mixer failed initializing: '%s'\n", Mix_GetError());
  }

  if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
    printf("Warning: Mixer failed to open audio channels: '%s'\n", Mix_GetError());
  }

  int ctAllocate = 32;
  int ctAllocated = Mix_AllocateChannels(ctAllocate);
  if(ctAllocated != ctAllocate) {
    printf("Warning: Mixer allocated %d channels instead of %d\n", ctAllocated, ctAllocate);
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
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    printf("SDL completely died\n");
  }
}

MRAGPP_NAMESPACE_END;
