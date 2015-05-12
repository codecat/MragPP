#ifndef MRAGPP_INPUT_H_INCLUDED
#define MRAGPP_INPUT_H_INCLUDED

#include "StdH.h"
#include "InputKeys.h"

union SDL_Event;

MRAGPP_NAMESPACE_BEGIN;

class MRAGPP_EXPORT CTouch
{
public:
  CTouch();
  ~CTouch();

public:
  long long m_iFingerID;
  bool m_bDown;
  Vector2f m_vPosition;
};

class CGame;
class MRAGPP_EXPORT CInput
{
private:
  CGame* inp_pGame;
  bool inp_aKeys[MKEY_NUM_SCANCODES];
  bool inp_aKeysPrev[MKEY_NUM_SCANCODES];
  int inp_iMouseX;
  int inp_iMouseY;
  bool inp_aMouse[MBUTTON_COUNT];
  bool inp_aMousePrev[MBUTTON_COUNT];
  CTouch inp_aTouches[TOUCH_FINGER_COUNT];

public:
  CInput();
  ~CInput();

  void Initialize(CGame* pGame);
  void HandleEvents(SDL_Event* e);

  bool IsKeyDown(int iKey);
  bool IsKeyUp(int iKey);
  bool IsKeyPressed(int iKey);

  int GetMouseX();
  int GetMouseY();

  bool IsMouseDown(int iButton);
  bool IsMouseUp(int iButton);
  bool IsMousePressed(int iButton);

  int GetTouchCount();
  CTouch* GetTouch(int iFinger);

private:
  CTouch* GetTouchById(long long iFingerID);
  CTouch* BeginTouch(long long iFingerID);
  void EndTouch(long long iFingerID);
};

MRAGPP_NAMESPACE_END;

#endif
