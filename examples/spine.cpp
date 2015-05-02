#include <math.h>

#include <Game.h>
#include <AnimationJson.h>
#include "example.h"

using namespace Scratch;
using namespace Mragpp;

class CSpine : public CGame
{
public:
	CFont m_font;
	CAnimationJson m_animation;
	int m_iCurrent;

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

	m_iCurrent = 0;
}

CSpine::~CSpine()
{
}

void CSpine::Initialize()
{
	m_font.Load("system.ttf", 32);

	m_animation.Load(this, "spineboy.atlas", "spineboy.json");
	m_animation.DumpInfo();

	m_iCurrent = 0;

	m_animation.SetAnimation(m_animation.GetAnimationName(m_iCurrent), true);

	Window.SetTitle("Example 03: Spine");

	CGame::Initialize();
}

void CSpine::Update()
{
	if(Input.IsKeyDown(MKEY_ESCAPE)) {
		Exit();
	}

	m_animation.Update(0.01f);

	if(Input.IsKeyPressed(MKEY_RETURN)) {
		if(++m_iCurrent >= m_animation.GetAnimationCount()) {
			m_iCurrent = 0;
		}
		m_animation.SetAnimation(m_animation.GetAnimationName(m_iCurrent), true);
	}

	CGame::Update();
}

void CSpine::Render()
{
	Renderer.SetColor(COL_BLACK | MRAG_ALPHA_OPAQUE);
	Renderer.Clear();

	Renderer.SetFont(m_font);
	Renderer.SetColor(COL_WHITE | MRAG_ALPHA_OPAQUE);
	Renderer.PutText(m_animation.GetAnimationName(m_iCurrent), 20, 20);

	m_animation.Render(Renderer, Vector2f(400, 700), Vector2f(0.75f, 0.75f));

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
