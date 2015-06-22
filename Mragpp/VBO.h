#ifndef MRAGPP_VBO_H_INCLUDED
#define MRAGPP_VBO_H_INCLUDED

#include "StdH.h"

MRAGPP_NAMESPACE_BEGIN;

class CVBO
{
public:
	unsigned int vbo_iVBO;
	unsigned int vbo_iIBO;

public:
	CVBO();
	~CVBO();

	/**
	 * @brief Clear Clears the VBO and deletes the buffers
	 */
	void Clear();
	/**
	 * @brief Set Sets the VBO and IBO buffers to the given vertex array
	 * @param vertices The vertex array
	 * @param ctVertices The amount of vertices that are in the array (excluding eventual texcoords)
	 * @param bWithTexCoords Whether the vertex array has texcoords at the end of the vertex array
	 */
	void Set(const float* vertices, int ctVertices, bool bWithTexCoords = FALSE);
};

MRAGPP_NAMESPACE_END;

#endif
