#ifndef MRAGPP_SHADER_H_INCLUDED
#define MRAGPP_SHADER_H_INCLUDED

#include "StdH.h"
#include "VBO.h"
#include "Texture.h"

MRAGPP_NAMESPACE_BEGIN;

class CGame;

class CShader
{
public:
	CGame* sha_pGame;

	unsigned int sha_iProgram;
	unsigned int sha_iShaderVertex;
	unsigned int sha_iShaderFragment;
	int sha_iPosAttrib;
	int sha_iTexCoordAttrib;
	CVBO sha_vbo;

	Scratch::StackArray<CTexture> sha_saSamplers;

	Scratch::String sha_strFragDataLocation;
	Scratch::String sha_strInPosName;
	Scratch::String sha_strInTexCoordName;

public:
	CShader();
	~CShader();

	bool LoadShader(const Scratch::Filename &fnm, int type);
	unsigned int CompileShader(const char* str, int type, bool &bSuccess);

	bool LinkProgram(CGame* pGame);

	bool LoadVertexShader(const Scratch::Filename &fnmVertex);
	bool LoadFragmentShader(const Scratch::Filename &fnmFragment);

	int GetUniform(const char* szUniform);

	void SetUniform1i(int iUniform, int iValue);
	void SetUniform1i(const char* szUniform, int iValue);

	void SetUniform1f(int iUniform, float fValue);
	void SetUniform1f(const char* szUniform, float fValue);

	void SetUniformSampler(int iUniform, CTexture &texture);
	void SetUniformSampler(const char* szUniform, CTexture &texture);

	void Use();
	void Release();

	void PutQuad(float x, float y, float w, float h);
};

MRAGPP_NAMESPACE_END;

#endif
