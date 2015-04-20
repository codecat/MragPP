#include "StdH.h"
#include "Input.h"
#include "InputKeys.h"
#include "Game.h"
#include "Message.h"

#include <SDL.h>

MRAGPP_NAMESPACE_BEGIN;

CTouch::CTouch()
{
  m_iFingerID = 0;
  m_bDown = false;
  m_vPosition = Vector2f(-1, -1);
}

CTouch::~CTouch()
{
}

CInput::CInput()
{
  inp_pGame = 0;
  for(int i=0; i<MKEY_NUM_SCANCODES; i++) {
    inp_aKeys[i] = false;
    inp_aKeysPrev[i] = false;
  }
  inp_iMouseX = 0;
  inp_iMouseY = 0;
  for(int i=0; i<MBUTTON_COUNT; i++) {
    inp_aMouse[i] = false;
    inp_aMousePrev[i] = false;
  }
}

CInput::~CInput()
{
}

void CInput::Initialize(CGame* pGame)
{
  inp_pGame = pGame;
}

void CInput::HandleEvents(SDL_Event* e)
{
  if(inp_pGame == 0) {
    return;
  }

  while(SDL_PollEvent(e)) {
    if(inp_pGame->gam_bCatchMessages) {
      if(!inp_pGame->MessageLoop(CMessage(e))) {
        continue;
      }
    }

    switch(e->type) {
    case SDL_QUIT:
      if(inp_pGame->OnClose()) {
        inp_pGame->Exit();
      }
      break;

    case SDL_KEYDOWN:
      inp_aKeysPrev[e->key.keysym.scancode] = inp_aKeys[e->key.keysym.scancode];
      inp_aKeys[e->key.keysym.scancode] = true;
      break;
    case SDL_KEYUP:
      inp_aKeysPrev[e->key.keysym.scancode] = inp_aKeys[e->key.keysym.scancode];
      inp_aKeys[e->key.keysym.scancode] = false;
      break;

    case SDL_MOUSEMOTION:
      inp_iMouseX = e->motion.x;
      inp_iMouseY = e->motion.y;
      break;

    case SDL_MOUSEBUTTONDOWN:
      inp_aMousePrev[e->button.button-1] = inp_aMouse[e->button.button-1];
      inp_aMouse[e->button.button-1] = true;
      break;
    case SDL_MOUSEBUTTONUP:
      inp_aMousePrev[e->button.button-1] = inp_aMouse[e->button.button-1];
      inp_aMouse[e->button.button-1] = false;
      break;

    case SDL_FINGERDOWN:
      {
        CTouch* pTouch = BeginTouch(e->tfinger.fingerId);
        if(pTouch != NULL) {
          pTouch->m_vPosition(1) = e->tfinger.x * (float)inp_pGame->gam_iWidth;
          pTouch->m_vPosition(2) = e->tfinger.y * (float)inp_pGame->gam_iHeight;
        }
      }
      break;
    case SDL_FINGERMOTION:
      {
        CTouch* pTouch = GetTouchById(e->tfinger.fingerId);
        if(pTouch != NULL) {
          pTouch->m_vPosition(1) = e->tfinger.x * (float)inp_pGame->gam_iWidth;
          pTouch->m_vPosition(2) = e->tfinger.y * (float)inp_pGame->gam_iHeight;
        }
      }
      break;
    case SDL_FINGERUP:
      EndTouch(e->tfinger.fingerId);
      break;

    case SDL_WINDOWEVENT:
      if(e->window.event == SDL_WINDOWEVENT_RESIZED) {
        int iNewW = 0, iNewH = 0;
        SDL_GetWindowSize(inp_pGame->Window, &iNewW, &iNewH);
        inp_pGame->gam_iWidth = iNewW;
        inp_pGame->gam_iHeight = iNewH;
      }
      break;
    }
  }
}

bool CInput::IsKeyDown(int iKey)
{
  return inp_aKeys[iKey];
}

bool CInput::IsKeyUp(int iKey)
{
  return !inp_aKeys[iKey];
}

bool CInput::IsKeyPressed(int iKey)
{
  bool ret = inp_aKeys[iKey] && !inp_aKeysPrev[iKey];
  if(ret) {
    inp_aKeysPrev[iKey] = inp_aKeys[iKey];
  }
  return ret;
}

int CInput::GetMouseX()
{
  return inp_iMouseX;
}

int CInput::GetMouseY()
{
  return inp_iMouseY;
}

bool CInput::IsMouseDown(int iButton)
{
  return inp_aMouse[iButton];
}

bool CInput::IsMouseUp(int iButton)
{
  return !inp_aMouse[iButton];
}

bool CInput::IsMousePressed(int iButton)
{
  bool ret = inp_aMouse[iButton] && !inp_aMousePrev[iButton];
  if(ret) {
    inp_aMousePrev[iButton] = inp_aMouse[iButton];
  }
  return ret;
}

int CInput::GetTouchCount()
{
  int ret = 0;
  for(int i=0; i<TOUCH_FINGER_COUNT; i++) {
    if(inp_aTouches[i].m_bDown) {
      ret++;
    }
  }
  return ret;
}

CTouch* CInput::GetTouch(int iFinger)
{
  int iCheck = 0;
  for(int i=0; i<TOUCH_FINGER_COUNT; i++) {
    CTouch &touch = inp_aTouches[i];
    if(touch.m_bDown) {
      if(iCheck == iFinger) {
        return &touch;
      }
      iCheck++;
    }
  }
  return NULL;
}

CTouch* CInput::GetTouchById(long long iFingerID)
{
  for(int i=0; i<TOUCH_FINGER_COUNT; i++) {
    if(inp_aTouches[i].m_iFingerID == iFingerID) {
      return &inp_aTouches[i];
    }
  }
  return NULL;
}

CTouch* CInput::BeginTouch(long long iFingerID)
{
  for(int i=0; i<TOUCH_FINGER_COUNT; i++) {
    if(!inp_aTouches[i].m_bDown) {
      inp_aTouches[i].m_iFingerID = iFingerID;
      inp_aTouches[i].m_bDown = true;
      return &inp_aTouches[i];
    }
  }
  return NULL;
}

void CInput::EndTouch(long long iFingerID)
{
  CTouch* pTouch = GetTouchById(iFingerID);
  if(pTouch == NULL) {
    return;
  }
  pTouch->m_bDown = false;
  pTouch->m_iFingerID = 0;
}

MRAGPP_NAMESPACE_END;
