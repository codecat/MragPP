#include <Game.h>
#include <SDL.h>
#include <GL/glew.h>

#include "example.h"

using namespace Scratch;
using namespace Mragpp;

class CShaderExample : public CGame
{
public:
	GLuint m_iProgram;
	GLint m_iVertexPos2DPosition;
	GLint m_iVertexPos2DTexCoord;
	GLint m_iFragmentFrameCount;
	GLint m_iFragmentSampler;
	GLuint m_iVBO;
	GLuint m_iIBO;

	CTexture m_texture;

	int m_iFrameCount;

public:
	CShaderExample();
	virtual ~CShaderExample();

	GLuint CompileShader(const char* str, GLuint type);

	virtual void Initialize();

	virtual void Update();
	virtual void Render();
};

CShaderExample::CShaderExample()
{
	gam_iWidth = 800;
	gam_iHeight = 600;

	m_iProgram = 0;
	m_iVertexPos2DPosition = -1;
	m_iVertexPos2DTexCoord = -1;
	m_iFragmentFrameCount = -1;
	m_iFragmentSampler = -1;
	m_iVBO = 0;
	m_iIBO = 0;

	m_iFrameCount = 0;

	//TODO: Check if this is really required before context is created
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

CShaderExample::~CShaderExample()
{
}

GLuint CShaderExample::CompileShader(const char* str, GLuint type)
{
	// create a new shader
	GLuint iShader = glCreateShader(type);
	const GLchar* aSourceVertex[] = { str };
	glShaderSource(iShader, 1, aSourceVertex, NULL);
	glCompileShader(iShader);

	// check if compiling went okay
	GLint bShaderCompiled = GL_FALSE;
	glGetShaderiv(iShader, GL_COMPILE_STATUS, &bShaderCompiled);
	if(bShaderCompiled != GL_TRUE) {
		// it did not.
		printf("Error compiling %sshader:\n", (type == GL_VERTEX_SHADER ? "vertex " : ""));
		int iLogLength = 0;
		int iMaxLength = 0;
		glGetShaderiv(iShader, GL_INFO_LOG_LENGTH, &iMaxLength);
		char* buffer = new char[iMaxLength];
		glGetShaderInfoLog(iShader, iMaxLength, &iLogLength, buffer);
		if(iLogLength > 0) {
			printf("%s\n", buffer);
		}
		delete[] buffer;
	}

	// return shader
	return iShader;
}

void CShaderExample::Initialize()
{
	Window.SetTitle("Example 06: Shaders");

	// create program
	m_iProgram = glCreateProgram();

	// create vertex shader
	GLuint iShaderVertex = CompileShader("#version 130\n"
																			 "in vec2 in_vPos;\n"
																			 "in vec2 in_vTexCoord;\n"
																			 "out vec2 s_vTexCoord;\n"
																			 "void main() {\n"
																			 "  gl_Position = vec4(in_vPos, 0, 1);\n"
																			 "  s_vTexCoord = (in_vTexCoord * vec2(1, -1) + vec2(1, 1)) / 2;\n"
																			 "}\n", GL_VERTEX_SHADER);

	// create fragment shader
	GLuint iShaderFragment = CompileShader("#version 130\n"
																				 "in vec2 s_vTexCoord;\n"
																				 "out vec4 s_colOut;\n"
																				 "uniform float s_fFrameCount;\n"
																				 "uniform sampler2DRect s_texSampler;\n"
																				 "void main() {\n"
																				 //"  s_colOut = vec4(1, 1, 0.5 + cos(s_fFrameCount / 20) * 0.5, 1);\n"
																				 "  s_colOut = texture(s_texSampler, s_vTexCoord * textureSize(s_texSampler));\n"
																				 "}\n", GL_FRAGMENT_SHADER);

	// attach shaders to program
	glAttachShader(m_iProgram, iShaderVertex);
	glAttachShader(m_iProgram, iShaderFragment);

	// explicitly define what the fragment data location is
	glBindFragDataLocation(m_iProgram, 0, "s_colOut");

	// link program
	glLinkProgram(m_iProgram);

	// check if program linking went okay
	GLint bProgramLinked = GL_FALSE;
	glGetProgramiv(m_iProgram, GL_LINK_STATUS, &bProgramLinked);
	if(bProgramLinked != GL_TRUE) {
		// it did not.
		printf("Error linking shader program:\n");
		int iLogLength = 0;
		int iMaxLength = 0;
		glGetProgramiv(m_iProgram, GL_INFO_LOG_LENGTH, &iMaxLength);
		char* buffer = new char[iMaxLength];
		glGetProgramInfoLog(m_iProgram, iMaxLength, &iLogLength, buffer);
		if(iLogLength > 0) {
			printf("%s\n", buffer);
		}
		delete[] buffer;
	}

	// get input attribute for vertex shader position
	m_iVertexPos2DPosition = glGetAttribLocation(m_iProgram, "in_vPos");
	if(m_iVertexPos2DPosition == -1) {
		printf("Couldn't find position attribute\n");
	}

	// get input attribute for vertex shader texcoord
	m_iVertexPos2DTexCoord = glGetAttribLocation(m_iProgram, "in_vTexCoord");
	if(m_iVertexPos2DTexCoord == -1) {
		printf("Couldn't find texcoord attribute\n");
	}

	// get uniform location for frame count
	m_iFragmentFrameCount = glGetUniformLocation(m_iProgram, "s_fFrameCount");
	if(m_iFragmentFrameCount == -1) {
		printf("Couldn't find frame count uniform\n");
	}

	// get uniform location for sampler
	m_iFragmentSampler = glGetUniformLocation(m_iProgram, "s_texSampler");
	if(m_iFragmentSampler == -1) {
		printf("Couldn't find sampler uniform\n");
	}

	//TODO: Check if this is required
	glClearColor(0, 0, 0, 1);

	// set up vbo
	GLfloat aVertexData[] = {
		// vertices
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f,

		// texcoords
		-1.0f, -1.0f,
		 1.0f, -1.0f,
		 1.0f,  1.0f,
		-1.0f,  1.0f
	};
	glGenBuffers(1, &m_iVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_iVBO);
	glBufferData(GL_ARRAY_BUFFER, 2 * 2 * 4 * sizeof(GLfloat), aVertexData, GL_STATIC_DRAW);

	// set up ibo
	GLuint aIndexData[] = { 0, 1, 2, 3 };
	glGenBuffers(1, &m_iIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), aIndexData, GL_STATIC_DRAW);

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

#define OGL_CHECK_ERROR() { \
		GLenum err = glGetError(); \
		if(err != GL_NO_ERROR) { \
			printf("OGL Error on line %d: %d (%s)\n", __LINE__, err, glewGetErrorString(err)); \
		} \
	}

void CShaderExample::Render()
{
	Renderer.SetColor(COL_BLACK | MRAG_ALPHA_OPAQUE);
	Renderer.Clear();

	// bind program
	glUseProgram(m_iProgram);

	// enable attributes
	glEnableVertexAttribArray(m_iVertexPos2DPosition);
	glEnableVertexAttribArray(m_iVertexPos2DTexCoord);

	// set layout of vertex data
	glBindBuffer(GL_ARRAY_BUFFER, m_iVBO);
	glVertexAttribPointer(m_iVertexPos2DPosition, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

	// set layout of texcoord data
	glVertexAttribPointer(m_iVertexPos2DTexCoord, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(8 * sizeof(GLfloat)));

	// set frame count uniform
	if(m_iFragmentFrameCount != -1) {
		glUniform1f(m_iFragmentFrameCount, (float)(m_iFrameCount++));
	}

	// set sampler uniform
	if(m_iFragmentSampler != -1) {
		glActiveTexture(GL_TEXTURE0);
		SDL_GL_BindTexture(m_texture, NULL, NULL);
		glUniform1i(m_iFragmentSampler, 0);
	}

	// set index data and render
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iIBO);
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

	// unbind samplers
	SDL_GL_UnbindTexture(m_texture);

	// disable attributes
	glDisableVertexAttribArray(m_iVertexPos2DTexCoord);
	glDisableVertexAttribArray(m_iVertexPos2DPosition);

	// unbind program
	glUseProgram(0);

	CGame::Render();
}

MAIN
{
	FindExampleContentPath();

	CShaderExample game;
	game.Run();

	return 0;
}
