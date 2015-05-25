#include "StdH.h"
#include "SoundChannel.h"

#include <SDL_mixer.h>

MRAGPP_NAMESPACE_BEGIN;

CSoundChannel::CSoundChannel(int iChannel)
{
  ch_iChannel = iChannel;
  printf("Channel: %d\n", iChannel);
  SetPanning(0.0f);
}

CSoundChannel::~CSoundChannel()
{
}

void CSoundChannel::Pause()
{
  Mix_Pause(ch_iChannel);
}

void CSoundChannel::Resume()
{
  Mix_Resume(ch_iChannel);
}

void CSoundChannel::Stop()
{
  Mix_HaltChannel(ch_iChannel);
}

void CSoundChannel::SetVolume(float fVolume)
{
  Mix_Volume(ch_iChannel, (int)(fVolume * MIX_MAX_VOLUME));
}

void CSoundChannel::SetPanning(float fPanning)
{
  float fLeft = -mthClamp(fPanning, -1.0f, 0.0f);
  float fRight = mthClamp(fPanning, 0.0f, 1.0f);
  Mix_SetPanning(ch_iChannel, 127 + (Uint8)(fLeft * 128.0f), 127 + (Uint8)(fRight * 128.0f));
}

MRAGPP_NAMESPACE_END;
