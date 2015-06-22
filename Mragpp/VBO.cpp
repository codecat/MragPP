#include "StdH.h"
#include "VBO.h"

#include <SDL.h>
#include <GL/glew.h>

MRAGPP_NAMESPACE_BEGIN;

CVBO::CVBO()
{
	vbo_iVBO = 0;
	vbo_iIBO = 0;
}

CVBO::~CVBO()
{
	Clear();
}

void CVBO::Clear()
{
	// delete buffers
	if(vbo_iVBO > 0) {
		glDeleteBuffers(1, &vbo_iVBO);
		vbo_iVBO = 0;
	}
	if(vbo_iIBO > 0) {
		glDeleteBuffers(1, &vbo_iIBO);
		vbo_iIBO = 0;
	}
}

void CVBO::Set(const float* vertices, int ctVertices, bool bWithTexCoords)
{
	// generate buffers if needed
	if(vbo_iVBO == 0 && vbo_iIBO == 0) {
		glGenBuffers(1, &vbo_iVBO);
		glGenBuffers(1, &vbo_iIBO);
	}
	ASSERT(vbo_iVBO > 0 && vbo_iIBO > 0);

	// set VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo_iVBO);
	if(bWithTexCoords) {
		glBufferData(GL_ARRAY_BUFFER, 2 * 2 * ctVertices * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	} else {
		glBufferData(GL_ARRAY_BUFFER,     2 * ctVertices * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	}

	// set IBO
	GLuint* pIBOBuffer = new GLuint[ctVertices];
	for(int i=0; i<ctVertices; i++) {
		pIBOBuffer[i] = i;
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_iIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ctVertices * sizeof(GLuint), pIBOBuffer, GL_STATIC_DRAW);
	delete[] pIBOBuffer;
}

MRAGPP_NAMESPACE_END;
