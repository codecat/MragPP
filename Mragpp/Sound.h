#ifndef MRAGPP_SOUND_H_INCLUDED
#define MRAGPP_SOUND_H_INCLUDED

#include "StdH.h"
#include "SoundChannel.h"

struct Mix_Chunk;

MRAGPP_NAMESPACE_BEGIN;

class MRAGPP_EXPORT CSound
{
public:
  Mix_Chunk* snd_pSample;

public:
  CSound();
  ~CSound();

  void Load(const char* szFilename);
  void Load(UBYTE* pubBuffer, int iLen);

  CSoundChannel Play();
  CSoundChannel Play(float fVolume);
  CSoundChannel Play(float fVolume, float fPanning);

  CSoundChannel Loop();
  CSoundChannel Loop(int iTicks);
  CSoundChannel Loop(int iTicks, float fVolume);
  CSoundChannel Loop(int iTicks, float fVolume, float fPanning);
};

MRAGPP_NAMESPACE_END;

#endif
