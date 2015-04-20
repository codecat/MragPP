#include "StdH.h"
#include "Message.h"

#include <SDL.h>

MRAGPP_NAMESPACE_BEGIN;

CMessage::CMessage(SDL_Event* e)
{
	msg_iType = e->type;

	msg_eKeyScan = (MragppKeys)e->key.keysym.scancode;
	msg_eKeyCode = (MragppKeys)e->key.keysym.sym;
	msg_iKeyMod = e->key.keysym.mod;
}

CMessage::~CMessage()
{
}

MRAGPP_NAMESPACE_END;
