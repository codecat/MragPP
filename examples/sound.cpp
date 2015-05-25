#include <Game.h>
#include <Sound.h>
#include "example.h"

using namespace Scratch;
using namespace Mragpp;

class CSoundExample : public CGame
{
public:
  CFont m_font;
  CSound m_Sound1;
  CSound m_Sound2;
  CSound m_Sound3;
  float m_fPan3;

public:
  CSoundExample();
  virtual ~CSoundExample();
	
  virtual void Initialize();

  virtual void Update();
  virtual void Render();
};

CSoundExample::CSoundExample()
{
  gam_iWidth = 800;
  gam_iHeight = 600;
  m_fPan3 = 1.0f;
}

CSoundExample::~CSoundExample()
{
}

void CSoundExample::Initialize()
{
  m_font.Load("system.ttf", 32);

  m_Sound1.Load("sound1.wav");
  m_Sound2.Load("sound2.wav");
  m_Sound3.Load("sound3.wav");

  Window.SetTitle("Example 04: Sound");

  CGame::Initialize();
}

void CSoundExample::Update()
{
  if(Input.IsKeyDown(MKEY_ESCAPE)) {
    Exit();
  }

  if(Input.IsKeyPressed(MKEY_1)) {
    m_Sound1.Play();
  }

  if(Input.IsKeyPressed(MKEY_2)) {
    m_Sound2.Loop(3000);
  }

  if(Input.IsKeyPressed(MKEY_3)) {
    m_Sound3.Play(1.0f, m_fPan3);
    m_fPan3 *= -1.0f;
  }

	CGame::Update();
}

void CSoundExample::Render()
{
  Renderer.SetColor(COL_BLACK | MRAG_ALPHA_OPAQUE);
  Renderer.Clear();

  Renderer.SetFont(m_font);
  Renderer.SetColor(COL_WHITE | MRAG_ALPHA_OPAQUE);
  Renderer.PutText("Press [1], [2], or [3]", 20, 20);

  CGame::Render();
}

int main()
{
  FindExampleContentPath();

  CSoundExample game;
  game.Run();

  return 0;
}
