#ifndef MRAGPP_MUSIC_H_INCLUDED
#define MRAGPP_MUSIC_H_INCLUDED

#include "StdH.h"

MRAGPP_NAMESPACE_BEGIN;

class MRAGPP_EXPORT CMusic
{
public:
  void* mus_pMusic;

public:
  CMusic();
  ~CMusic();

  void Load(const char* szFilename);
  void Load(UBYTE* pubBuffer, int iLen);

  //NOTE: These 4 are global across all CMusic objects due to the nature of SDL_mixer
  void Pause();
  void Resume();
  void Rewind();
  void SetPosition(double fAt);

  void Play(bool bLoop);
  void FadeIn(int iDuration, bool bLoop);
  void FadeIn(int iDuration, double fAt, bool bLoop);
};

MRAGPP_NAMESPACE_END;

#endif
