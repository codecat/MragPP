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

	msg_strTextInput = e->text.text;

	msg_strComposition = e->edit.text;
	msg_iEditCursor = e->edit.start;
	msg_iEditSelection = e->edit.length;
}

CMessage::~CMessage()
{
}

MRAGPP_NAMESPACE_END;
