#include "StdH.h"
#include "Engine.h"
#include "Game.h"

#include <cstdio>
#ifdef _MSC_VER
#include <Windows.h>
#include <Psapi.h>
#endif

#if _DEBUG && WINDOWS
#pragma comment(lib, "psapi.lib")
#endif

#include <SDL.h>

MRAGPP_NAMESPACE_BEGIN;

CGame::CGame()
{
  InitializeEngine();

  gam_strWindowTitle = "Mrag++ Window";
  gam_iWidth = 1024;
  gam_iHeight = 768;
  gam_ulWindowFlags = 0;
  gam_bRunning = true;
#if !WINDOWS
  gam_strSystemFont = "System.ttf";
#endif
  Input.Initialize(this);
}

CGame::~CGame()
{
  //EndEngine();
}

void CGame::LoadSystemFont(int iSize)
{
  gam_fntSystem.Load(gam_strSystemFont, iSize);
}

void CGame::Run()
{
  Window.Create(gam_strWindowTitle, gam_iWidth, gam_iHeight, gam_ulWindowFlags);
  Renderer.Create(Window);

  Initialize();

  SDL_Event e;

  while(gam_bRunning) {
    Input.HandleEvents(&e);

    Update();
    Render();

    Renderer.Present();
    SDL_Delay(16);
  }
}

void CGame::Exit()
{
  gam_bRunning = false;
}

void CGame::Initialize()
{

}

bool CGame::OnClose()
{
  return true;
}

void CGame::Update()
{
  Paths.Update();
}

void CGame::Render()
{
  Paths.Render();

#if _DEBUG && WINDOWS
  if(Input.IsKeyDown(MKEY_F1)) {
    PROCESS_MEMORY_COUNTERS counters;
    GetProcessMemoryInfo(GetCurrentProcess(), &counters, sizeof(counters));

    Scratch::CString strMemoryInfo;
    strMemoryInfo.SetF("Memory in use: %d KB", counters.WorkingSetSize / 1000);

    Renderer.PushColor(COL_CYAN | MRAG_ALPHA_OPAQUE);
    Renderer.PushFont(gam_fntSystem);

    Renderer.PutText(strMemoryInfo, 0, 0);

    Renderer.PopColor();
    Renderer.PopFont();
  }
#endif
}

MRAGPP_NAMESPACE_END;
