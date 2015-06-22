#include <Game.h>
#include <Shader.h>

#include <SDL.h>
#include <GL/glew.h>

#include "example.h"

using namespace Scratch;
using namespace Mragpp;

class CShaderExample : public CGame
{
public:
	CShader m_shader;
	CTexture m_texture;

	int m_iFrameCount;

public:
	CShaderExample();
	virtual ~CShaderExample();

	virtual void Initialize();

	virtual void Update();
	virtual void Render();
};

CShaderExample::CShaderExample()
{
	gam_iWidth = 800;
	gam_iHeight = 600;

	m_iFrameCount = 0;
}

CShaderExample::~CShaderExample()
{
}

void CShaderExample::Initialize()
{
	Window.SetTitle("Example 06: Shaders");

	// load the sader
	m_shader.LoadVertexShader("shader.vtx.glsl");
	m_shader.LoadFragmentShader("shader.frg.glsl");
	m_shader.LinkProgram(this);

	// load a texture
	m_texture.Load(Renderer, "texture.png");

	CGame::Initialize();
}

void CShaderExample::Update()
{
	if(Input.IsKeyDown(MKEY_ESCAPE)) {
		Exit();
	}

	CGame::Update();
}

void CShaderExample::Render()
{
	Renderer.SetColor(COL_BLACK | MRAG_ALPHA_OPAQUE);
	Renderer.Clear();

	m_shader.Use();
	m_shader.SetUniform1f("s_fFrameCount", (float)(m_iFrameCount++));
	m_shader.SetUniformSampler("s_texSampler", m_texture);
	m_shader.PutQuad(100, 100, 300, 250);
	m_shader.Release();

	CGame::Render();
}

MAIN
{
	FindExampleContentPath();

	CShaderExample game;
	game.Run();

	return 0;
}
