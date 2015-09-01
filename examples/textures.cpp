#include <Game.h>

#include "example.h"

using namespace Scratch;
using namespace Mragpp;

class CTextures : public CGame
{
public:
	CTexture m_texTest;

public:
	CTextures();
	virtual ~CTextures();
	
	virtual void Initialize();
	
	virtual void Update();
	virtual void Render();
};

CTextures::CTextures()
{
	gam_iWidth = 800;
	gam_iHeight = 600;
}

CTextures::~CTextures()
{
}

void CTextures::Initialize()
{
	Window.SetTitle("Example 08: Textures");
	
	m_texTest.Load(Renderer, "avatar.png");
	
	CGame::Initialize();
}

void CTextures::Update()
{
	if(Input.IsKeyDown(MKEY_ESCAPE)) {
		Exit();
	}
	
	CGame::Update();
}

void CTextures::Render()
{
	Renderer.SetColor(COL_BLACK | MRAG_ALPHA_OPAQUE);
	Renderer.Clear();
	
	static float fRot = 0.0f;
	
	Renderer.PutTexture(m_texTest, 0, 0);
	Renderer.PutTexture(m_texTest, 200, 0, 400, 200);
	Renderer.PutTextureCenter(m_texTest, gam_iWidth / 2, gam_iHeight);
	Renderer.PutTextureRight(m_texTest, gam_iWidth, 0);
	Renderer.PutTexture(m_texTest, gam_iWidth / 2, gam_iHeight / 2, 184, 184, fRot);
	Renderer.PutTexture(m_texTest, gam_iWidth / 4, gam_iHeight / 2, 184, 184, fRot, Vector2f(0, 0));
	Renderer.PutTexture(m_texTest, gam_iWidth / 4 * 3, gam_iHeight / 2, 184, 184, fRot, Vector2f(184, 184));
	
	fRot += 1.0f; // Rotation in degrees
	
	CGame::Render();
}

MAIN
{
	FindExampleContentPath();
	
	CTextures game;
	game.Run();
	
	return 0;
}
