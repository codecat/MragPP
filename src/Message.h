#ifndef MRAGPP_MESSAGE_H_INCLUDED
#define MRAGPP_MESSAGE_H_INCLUDED

#include "StdH.h"
#include "InputKeys.h"

union SDL_Event;

MRAGPP_NAMESPACE_BEGIN;

class MRAGPP_EXPORT CMessage
{
public:
	ULONG msg_iType;

	MragppKeys msg_eKeyScan;
	MragppKeys msg_eKeyCode;
	unsigned short msg_iKeyMod;

public:
	CMessage(SDL_Event* e);
	~CMessage();
};

MRAGPP_NAMESPACE_END;

#endif
