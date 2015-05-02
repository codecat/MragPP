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
	gam_iWidth = 1024;
	gam_iHeight = 768;
}

CSpine::~CSpine()
{
}

void CSpine::Initialize()
{
	m_animation.Load(this, "spineboy.atlas", "spineboy.json");
	m_animation.DumpInfo();
	m_animation.SetAnimation("idle", true);

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

	m_animation.Render(Renderer, Vector2f(200, 600), Vector2f(0.75f, 0.75f));

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
