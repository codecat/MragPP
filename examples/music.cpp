#include <Game.h>
#include <Music.h>
#include "example.h"

using namespace Scratch;
using namespace Mragpp;

class CMusicExample : public CGame
{
public:
  CFont m_font;
  CMusic m_music;

public:
  CMusicExample();
  virtual ~CMusicExample();

  virtual void Initialize();

  virtual void Update();
  virtual void Render();
};

CMusicExample::CMusicExample()
{
  gam_iWidth = 800;
  gam_iHeight = 600;
}

CMusicExample::~CMusicExample()
{
}

void CMusicExample::Initialize()
{
  m_font.Load("system.ttf", 32);

  m_music.Load("music.mp3");
  m_music.Play(true);

  Window.SetTitle("Example 05: Music");

  CGame::Initialize();
}

void CMusicExample::Update()
{
  if(Input.IsKeyDown(MKEY_ESCAPE)) {
    Exit();
  }

  CGame::Update();
}

void CMusicExample::Render()
{
  Renderer.SetColor(COL_BLACK | MRAG_ALPHA_OPAQUE);
  Renderer.Clear();

  Renderer.SetFont(m_font);
  Renderer.SetColor(COL_WHITE | MRAG_ALPHA_OPAQUE);
  Renderer.PutText("NP: \"Glorious Morning\" by Waterflame", 20, 20);

  CGame::Render();
}

MAIN
{
  FindExampleContentPath();

  CMusicExample game;
  game.Run();

  return 0;
}
