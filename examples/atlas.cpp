#include <Game.h>
#include <AnimationAtlas.h>

#include "example.h"

using namespace Scratch;
using namespace Mragpp;

class CAtlas : public CGame
{
public:
	CAnimationAtlas m_atlas;

public:
	CAtlas();
	virtual ~CAtlas();

	virtual void Initialize();

	virtual void Update();
	virtual void Render();
};

CAtlas::CAtlas()
{
	gam_iWidth = 800;
	gam_iHeight = 600;
}

CAtlas::~CAtlas()
{
}

void CAtlas::Initialize()
{
	Window.SetTitle("Example 02: Atlas");

	CGame::Initialize();

	m_atlas.Load(this, "animation.atlas");
}

void CAtlas::Update()
{
	if(Input.IsKeyDown(MKEY_ESCAPE)) {
		Exit();
	}

	CGame::Update();
}

void CAtlas::Render()
{
	Renderer.SetColor(COL_BLACK | MRAG_ALPHA_OPAQUE);
	Renderer.Clear();

	m_atlas.Render(Renderer, Vector2f(100, 100));

	CGame::Render();
}

MAIN
{
	FindExampleContentPath();

	CAtlas game;
	game.Run();

	return 0;
}
