#include <Game.h>

using namespace Scratch;
using namespace Mragpp;

class CBasic : public CGame
{
public:
	CBasic();
	virtual ~CBasic();
	
	virtual void Initialize();
	
	virtual void Update();
	virtual void Render();
};

CBasic::CBasic()
{
	gam_iWidth = 800;
	gam_iHeight = 600;
}

CBasic::~CBasic()
{
}

void CBasic::Initialize()
{
	Window.SetTitle("Example 01: Basic");

	CGame::Initialize();
}

void CBasic::Update()
{
	if(Input.IsKeyDown(MKEY_ESCAPE)) {
		Exit();
	}

	CGame::Update();
}

void CBasic::Render()
{
	Renderer.SetColor(COL_BLACK | MRAG_ALPHA_OPAQUE);
	Renderer.Clear();

	CGame::Render();
}

int main()
{
	CBasic game;
	game.Run();

	return 0;
}
