#include <math.h>

#include <Game.h>
#include <AnimationJson.h>
#include "example.h"

using namespace Scratch;
using namespace Mragpp;

class CSpine : public CGame
{
public:
	CAnimationJson m_animation;

public:
	CSpine();
	virtual ~CSpine();

	virtual void Initialize();

	virtual void Update();
	virtual void Render();
};

CSpine::CSpine()
{
	gam_iWidth = 800;
	gam_iHeight = 600;
}

CSpine::~CSpine()
{
}

void CSpine::Initialize()
{
	m_animation.Load(this, "skeleton.atlas", "skeleton.json");
	m_animation.SetAnimation("animation", true);

	Window.SetTitle("Example 03: Spine");

	CGame::Initialize();
}

void CSpine::Update()
{
	if(Input.IsKeyDown(MKEY_ESCAPE)) {
		Exit();
	}

	m_animation.Update(0.01f);

	CGame::Update();
}

void CSpine::Render()
{
	Renderer.SetColor(COL_BLACK | MRAG_ALPHA_OPAQUE);
	Renderer.Clear();

	m_animation.Render(Renderer, Vector2f(200, 200));

	Renderer.SetColor(COL_RED | MRAG_ALPHA_OPAQUE);

	CGame::Render();
}

int main()
{
	FindExampleContentPath();

	CSpine game;
	game.Run();

	return 0;
}
