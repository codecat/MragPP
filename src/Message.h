#ifndef MRAGPP_MESSAGE_H_INCLUDED
#define MRAGPP_MESSAGE_H_INCLUDED

#include "StdH.h"
#include "InputKeys.h"

union SDL_Event;

#define MRAG_MSGTYPE_KEYDOWN (0x300)
#define MRAG_MSGTYPE_KEYUP (0x301)
#define MRAG_MSGTYPE_TEXTEDITING (0x302)
#define MRAG_MSGTYPE_TEXTINPUT (0x303)

MRAGPP_NAMESPACE_BEGIN;

class MRAGPP_EXPORT CMessage
{
public:
  ULONG msg_iType;

  MragppKeys msg_eKeyScan;
  MragppKeys msg_eKeyCode;
  MragppKeymods msg_eKeyMod;

  Scratch::CString msg_strTextInput;

  Scratch::CString msg_strComposition;
  int msg_iEditCursor;
  int msg_iEditSelection;

public:
  CMessage(SDL_Event* e);
  ~CMessage();
};

MRAGPP_NAMESPACE_END;

#endif
