#include "StdH.h"
#include "Shader.h"
#include "Game.h"

#include <GL/glew.h>

using namespace Scratch;

#define OGL_CHECK_ERROR() { \
		GLenum err = glGetError(); \
		if(err != GL_NO_ERROR) { \
			printf("OGL Error on line %d: %d (%s)\n", __LINE__, err, glewGetErrorString(err)); \
		} \
	}

MRAGPP_NAMESPACE_BEGIN;

CShader::CShader()
{
	sha_bReady = false;

	sha_iProgram = 0;
	sha_iShaderVertex = 0;
	sha_iShaderFragment = 0;
	sha_iPosAttrib = -1;
	sha_iTexCoordAttrib = -1;

	sha_strFragDataLocation = "s_colOut";
	sha_strInPosName = "in_vPos";
	sha_strInTexCoordName = "in_vTexCoord";
}

CShader::~CShader()
{
	Clear();
}

void CShader::Clear()
{
	if(sha_iProgram > 0) {
		glDeleteProgram(sha_iProgram);
		sha_iProgram = 0;
	}
	if(sha_iShaderVertex > 0) {
		glDeleteShader(sha_iShaderVertex);
		sha_iShaderVertex = 0;
	}
	if(sha_iShaderFragment > 0) {
		glDeleteShader(sha_iShaderFragment);
		sha_iShaderFragment = 0;
	}
	sha_bReady = false;
}

bool CShader::LoadShader(const Filename &fnm, int type)
{
	// load the code from file
	String strCode;
	FileStream fs;
	fs.Open(fnm, "r");
	while(!fs.AtEOF()) {
		strCode += fs.ReadLine() + "\n";
	}
	fs.Close();

	// create the program if we don't have one yet
	if(sha_iProgram == 0) {
		sha_iProgram = glCreateProgram();
	}

	// compile the shader and attach to the program it if it succeeded
	bool bSuccess = false;
	GLuint iShader = CompileShader(strCode, type, bSuccess);
	if(bSuccess) {
		glAttachShader(sha_iProgram, iShader);
		if(type == GL_VERTEX_SHADER) {
			sha_iShaderVertex = iShader;
		} else if(type == GL_FRAGMENT_SHADER) {
			sha_iShaderFragment = iShader;
		}
	}
	return bSuccess;
}

unsigned int CShader::CompileShader(const char* str, int type, bool &bSuccess)
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

		// report it back
		bSuccess = false;
		// and delete the shader
		glDeleteShader(iShader);
	} else {
		// it worked!
		bSuccess = true;
	}

	// return shader
	return iShader;
}

bool CShader::LinkProgram(CGame* pGame)
{
	sha_pGame = pGame;

	// explicitly define what the fragment data location is
	glBindFragDataLocation(sha_iProgram, 0, sha_strFragDataLocation);

	// link the program
	glLinkProgram(sha_iProgram);

	// check if program linking went okay
	GLint bProgramLinked = GL_FALSE;
	glGetProgramiv(sha_iProgram, GL_LINK_STATUS, &bProgramLinked);
	if(bProgramLinked != GL_TRUE) {
		// it did not.
		printf("Error linking shader program:\n");
		int iLogLength = 0;
		int iMaxLength = 0;
		glGetProgramiv(sha_iProgram, GL_INFO_LOG_LENGTH, &iMaxLength);
		char* buffer = new char[iMaxLength];
		glGetProgramInfoLog(sha_iProgram, iMaxLength, &iLogLength, buffer);
		if(iLogLength > 0) {
			printf("%s\n", buffer);
		}
		delete[] buffer;
		return false;
	}

	// get input attribute for vertex shader position
	sha_iPosAttrib = glGetAttribLocation(sha_iProgram, sha_strInPosName);
	if(sha_iPosAttrib == -1) {
		printf("Couldn't find position attribute\n");
	}

	// get input attribute for vertex shader texcoord
	sha_iTexCoordAttrib = glGetAttribLocation(sha_iProgram, sha_strInTexCoordName);
	if(sha_iTexCoordAttrib == -1) {
		// don't report, because this is most likely intentional
		//printf("Couldn't find texcoord attribute\n");
	}

	sha_bReady = true;
	return true;
}

bool CShader::LoadVertexShader(const Filename &fnmVertex)
{
	return LoadShader(fnmVertex, GL_VERTEX_SHADER);
}

bool CShader::LoadFragmentShader(const Filename &fnmFragment)
{
	return LoadShader(fnmFragment, GL_FRAGMENT_SHADER);
}

int CShader::GetUniform(const char* szUniform)
{
	return glGetUniformLocation(sha_iProgram, szUniform);
}

void CShader::SetUniform1i(int iUniform, int iValue)
{
	ASSERT(iUniform != -1);
	glUniform1i(iUniform, iValue);
}

void CShader::SetUniform1i(const char* szUniform, int iValue)
{
	SetUniform1i(GetUniform(szUniform), iValue);
}

void CShader::SetUniform1f(int iUniform, float fValue)
{
	ASSERT(iUniform != -1);
	glUniform1f(iUniform, fValue);
}

void CShader::SetUniform1f(const char* szUniform, float fValue)
{
	SetUniform1f(GetUniform(szUniform), fValue);
}

void CShader::SetUniform2f(int iUniform, const Vector2f &v)
{
	ASSERT(iUniform != -1);
	glUniform2f(iUniform, v(1), v(2));
}

void CShader::SetUniform2f(const char* szUniform, const Vector2f &v)
{
	SetUniform2f(GetUniform(szUniform), v);
}

void CShader::SetUniform3f(int iUniform, const Vector3f &v)
{
	ASSERT(iUniform != -1);
	glUniform3f(iUniform, v(1), v(2), v(3));
}

void CShader::SetUniform3f(const char* szUniform, const Vector3f &v)
{
	SetUniform3f(GetUniform(szUniform), v);
}

void CShader::SetUniform3f(int iUniform, COLOR col)
{
	ASSERT(iUniform != -1);
	COLOR_VALUE r, g, b;
	MRAG_COLOR_EXPLODE_RGB(col, r, g, b);
	glUniform3f(iUniform, r / 255.0f, g / 255.0f, b / 255.0f);
}

void CShader::SetUniform3f(const char* szUniform, COLOR col)
{
	SetUniform3f(GetUniform(szUniform), col);
}

void CShader::SetUniform4f(int iUniform, const Vector4f &v)
{
	ASSERT(iUniform != -1);
	glUniform4f(iUniform, v(1), v(2), v(3), v(4));
}

void CShader::SetUniform4f(const char* szUniform, const Vector4f &v)
{
	SetUniform4f(GetUniform(szUniform), v);
}

void CShader::SetUniform4f(int iUniform, COLOR col)
{
	ASSERT(iUniform != -1);
	COLOR_VALUE r, g, b, a;
	MRAG_COLOR_EXPLODE_RGBA(col, r, g, b, a);
	glUniform4f(iUniform, r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

void CShader::SetUniform4f(const char* szUniform, COLOR col)
{
	SetUniform4f(GetUniform(szUniform), col);
}

void CShader::SetUniformSampler(int iUniform, CTexture &texture)
{
	ASSERT(iUniform != -1);

	int iSlot = sha_saSamplers.Count();

	glActiveTexture(GL_TEXTURE0 + iSlot);
	SDL_GL_BindTexture(texture, NULL, NULL);
	glUniform1i(iUniform, iSlot);

	sha_saSamplers.Push(&texture);
}

void CShader::SetUniformSampler(const char* szUniform, CTexture &texture)
{
	SetUniformSampler(GetUniform(szUniform), texture);
}

#define X_TO_GL(x) (((2.0f / (float)sha_pGame->gam_iWidth) * (x)) - 1.0f)
#define Y_TO_GL(y) -(((2.0f / (float)sha_pGame->gam_iHeight) * (y)) - 1.0f)

void CShader::Use()
{
	ASSERT(sha_saSamplers.Count() == 0);

	// bind program
	glUseProgram(sha_iProgram);

	// enable attributes
	glEnableVertexAttribArray(sha_iPosAttrib);
	glEnableVertexAttribArray(sha_iTexCoordAttrib);
}

void CShader::Release()
{
	// unbind samplers
	while(sha_saSamplers.Count() > 0) {
		glActiveTexture(GL_TEXTURE0 + sha_saSamplers.Count() - 1);
		SDL_GL_UnbindTexture(*sha_saSamplers.Pop());
	}

	// disable attributes
	glDisableVertexAttribArray(sha_iPosAttrib);
	glDisableVertexAttribArray(sha_iTexCoordAttrib);

	// unbind program
	glUseProgram(0);
}

void CShader::PutQuad(float x, float y, float w, float h)
{
	float fTopLeftX = X_TO_GL(x);
	float fTopLeftY = Y_TO_GL(y);
	float fBotRightX = X_TO_GL(x + w);
	float fBotRightY = Y_TO_GL(y + h);

	if(sha_saSamplers.Count() > 0) {
		float aVertexData[] = {
			// vertices
			/*
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f,
			*/
			fTopLeftX, fTopLeftY,
			fBotRightX, fTopLeftY,
			fBotRightX, fBotRightY,
			fTopLeftX, fBotRightY,

			// texcoords
			-1.0f, -1.0f,
			 1.0f, -1.0f,
			 1.0f,  1.0f,
			-1.0f,  1.0f
		};
		sha_vbo.Set(aVertexData, 4, true);
	} else {
		float aVertexData[] = {
			// vertices
			fTopLeftX, fTopLeftY,
			fBotRightX, fTopLeftY,
			fBotRightX, fBotRightY,
			fTopLeftX, fBotRightY
		};
		sha_vbo.Set(aVertexData, 4, false);
	}

	// set layout of vertex data
	glBindBuffer(GL_ARRAY_BUFFER, sha_vbo.vbo_iVBO);
	glVertexAttribPointer(sha_iPosAttrib, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	// set layout of texcoord data if needed
	if(sha_saSamplers.Count() > 0) {
		glVertexAttribPointer(sha_iTexCoordAttrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(8 * sizeof(GLfloat)));
	}

	// set index data and render
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sha_vbo.vbo_iIBO);
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
}

#undef XY_TO_GL

MRAGPP_NAMESPACE_END;
