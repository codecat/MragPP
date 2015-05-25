#include "StdH.h"
#include "Sound.h"

#include <SDL_mixer.h>

MRAGPP_NAMESPACE_BEGIN;

CSound::CSound()
{
  snd_pSample = NULL;
}

CSound::~CSound()
{
  if(snd_pSample != NULL) {
    Mix_FreeChunk(snd_pSample);
  }
}

void CSound::Load(const char* szFilename)
{
  snd_pSample = Mix_LoadWAV(szFilename);
}

void CSound::Load(UBYTE* pubBuffer, int iLen)
{
  snd_pSample = Mix_LoadWAV_RW(SDL_RWFromMem(pubBuffer, iLen), 0);
}

CSoundChannel CSound::Play()
{
  ASSERT(snd_pSample != NULL);
  return CSoundChannel(Mix_PlayChannel(-1, snd_pSample, 0));
}

CSoundChannel CSound::Play(float fVolume)
{
  ASSERT(snd_pSample != NULL);
  CSoundChannel ret(Mix_PlayChannel(-1, snd_pSample, 0));
  ret.SetVolume(fVolume);
  return ret;
}

CSoundChannel CSound::Play(float fVolume, float fPanning)
{
  ASSERT(snd_pSample != NULL);
  CSoundChannel ret(Mix_PlayChannel(-1, snd_pSample, 0));
  ret.SetVolume(fVolume);
  ret.SetPanning(fPanning);
  return ret;
}

CSoundChannel CSound::Loop()
{
  ASSERT(snd_pSample != NULL);
  return CSoundChannel(Mix_PlayChannel(-1, snd_pSample, -1));
}

CSoundChannel CSound::Loop(int iTicks)
{
  ASSERT(snd_pSample != NULL);
  return CSoundChannel(Mix_PlayChannelTimed(-1, snd_pSample, -1, iTicks));
}

CSoundChannel CSound::Loop(int iTicks, float fVolume)
{
  ASSERT(snd_pSample != NULL);
  CSoundChannel ret(Mix_PlayChannelTimed(-1, snd_pSample, -1, iTicks));
  ret.SetVolume(fVolume);
  return ret;
}

CSoundChannel CSound::Loop(int iTicks, float fVolume, float fPanning)
{
  ASSERT(snd_pSample != NULL);
  CSoundChannel ret(Mix_PlayChannelTimed(-1, snd_pSample, -1, iTicks));
  ret.SetVolume(fVolume);
  ret.SetPanning(fPanning);
  return ret;
}

MRAGPP_NAMESPACE_END;
