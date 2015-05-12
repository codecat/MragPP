#include "StdH.h"
#include "Message.h"

#include <SDL.h>

MRAGPP_NAMESPACE_BEGIN;

CMessage::CMessage(SDL_Event* e)
{
  msg_iType = e->type;

  if(msg_iType == MRAG_MSGTYPE_KEYDOWN || msg_iType == MRAG_MSGTYPE_KEYUP) {
    msg_eKeyScan = (MragppKeys)e->key.keysym.scancode;
    msg_eKeyCode = (MragppKeys)e->key.keysym.sym;
    msg_eKeyMod = (MragppKeymods)e->key.keysym.mod;

  } else if(msg_iType == MRAG_MSGTYPE_TEXTINPUT) {
    msg_strTextInput = e->text.text;

  } else if(msg_iType == MRAG_MSGTYPE_TEXTEDITING) {
    msg_strComposition = e->edit.text;
    msg_iEditCursor = e->edit.start;
    msg_iEditSelection = e->edit.length;
  }
}

CMessage::~CMessage()
{
}

MRAGPP_NAMESPACE_END;
