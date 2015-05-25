#include "StdH.h"
#include "Music.h"

#include <SDL_mixer.h>

MRAGPP_NAMESPACE_BEGIN;

CMusic::CMusic()
{
  mus_pMusic = NULL;
}

CMusic::~CMusic()
{
  if(mus_pMusic != NULL) {
    Mix_FreeMusic((Mix_Music*)mus_pMusic);
  }
}

void CMusic::Load(const char* szFilename)
{
  mus_pMusic = Mix_LoadMUS(szFilename);
}

void CMusic::Load(UBYTE *pubBuffer, int iLen)
{
  mus_pMusic = Mix_LoadMUS_RW(SDL_RWFromMem(pubBuffer, iLen), 0);
}

void CMusic::Pause()
{
  Mix_PauseMusic();
}

void CMusic::Resume()
{
  Mix_ResumeMusic();
}

void CMusic::Rewind()
{
  Mix_RewindMusic();
}

void CMusic::SetPosition(double fAt)
{
  Mix_SetMusicPosition(fAt);
}

void CMusic::Play(bool bLoop)
{
  ASSERT(mus_pMusic != NULL);
  Mix_PlayMusic((Mix_Music*)mus_pMusic, bLoop ? -1 : 0);
}

void CMusic::FadeIn(int iDuration, bool bLoop)
{
  ASSERT(mus_pMusic != NULL);
  Mix_FadeInMusic((Mix_Music*)mus_pMusic, bLoop ? -1 : 0, iDuration);
}

void CMusic::FadeIn(int iDuration, double fAt, bool bLoop)
{
  ASSERT(mus_pMusic != NULL);
  Mix_FadeInMusicPos((Mix_Music*)mus_pMusic, bLoop ? -1 : 0, iDuration, fAt);
}

MRAGPP_NAMESPACE_END;
