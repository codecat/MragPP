#include <Game.h>

#include "example.h"

using namespace Scratch;
using namespace Mragpp;

class CCubes : public CGame
{
public:
	CCubes();
	virtual ~CCubes();
	
	virtual void Initialize();
	
	virtual void Update();
	virtual void Render();
};

CCubes::CCubes()
{
	gam_iWidth = 800;
	gam_iHeight = 600;
}

CCubes::~CCubes()
{
}

void CCubes::Initialize()
{
	Window.SetTitle("Example 07: Cubes");
	
	CGame::Initialize();
}

void CCubes::Update()
{
	if(Input.IsKeyDown(MKEY_ESCAPE)) {
		Exit();
	}
	
	CGame::Update();
}

void CCubes::Render()
{
	Renderer.SetColor(COL_BLACK | MRAG_ALPHA_OPAQUE);
	Renderer.Clear();
	
	Renderer.SetColor(COL_RED | MRAG_ALPHA_OPAQUE);
	Renderer.FillRectangle(50, 50, 50, 50);
	
	Renderer.SetColor(COL_GREEN | MRAG_ALPHA_OPAQUE);
	Renderer.FillRectangle(150, 50, 50, 50);
	
	Renderer.SetColor(COL_BLUE | MRAG_ALPHA_OPAQUE);
	Renderer.FillRectangle(250, 50, 50, 50);
	
	Renderer.SetColor(COL_RED | MRAG_ALPHA_OPAQUE);
	Renderer.PutRectangle(50, 150, 50, 50);
	
	Renderer.SetColor(COL_GREEN | MRAG_ALPHA_OPAQUE);
	Renderer.PutRectangle(150, 150, 50, 50);
	
	Renderer.SetColor(COL_BLUE | MRAG_ALPHA_OPAQUE);
	Renderer.PutRectangle(250, 150, 50, 50);
	
	CGame::Render();
}

MAIN
{
	CCubes game;
	game.Run();
	
	return 0;
}
