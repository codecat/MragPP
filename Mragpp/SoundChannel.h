#ifndef MRAGPP_SOUNDCHANNEL_INCLUDED
#define MRAGPP_SOUNDCHANNEL_INCLUDED

#include "StdH.h"

MRAGPP_NAMESPACE_BEGIN;

class MRAGPP_EXPORT CSoundChannel
{
public:
  int ch_iChannel;

public:
  CSoundChannel(int iChannel);
  ~CSoundChannel();

  void Pause();
  void Resume();
  void Stop();
  void SetVolume(float fVolume);
  void SetPanning(float fPanning);
};

MRAGPP_NAMESPACE_END;

#endif
