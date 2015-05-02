#include <math.h>

#include <Game.h>
#include "example.h"

#include "spine/spine.h"
#include "spine/extension.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>

#ifndef SPINE_MESH_VERTEX_COUNT_MAX
#define SPINE_MESH_VERTEX_COUNT_MAX 1000
#endif

using namespace Scratch;
using namespace Mragpp;

struct SDLVertex
{
	COLOR colColor;
	Vector2f vPosition;
	Vector2f vTexCoords;
};

static CRenderer* _pRenderer = NULL;

// Functions that have to be implemented for the spine-c runtime
void _spAtlasPage_createTexture (spAtlasPage* self, const char* path)
{
	CTexture* pTexture = new CTexture();
	pTexture->Load(*_pRenderer, path);
	self->rendererObject = (void*)pTexture;
	self->width = pTexture->tex_iWidth;
	self->height = pTexture->tex_iHeight;
}

void _spAtlasPage_disposeTexture (spAtlasPage* self)
{
	delete (CTexture*)self->rendererObject;
}

char* _spUtil_readFile (const char* path, int* length)
{
	return _readFile(path, length);
}

class CBasic : public CGame
{
public:
	spSkeleton* m_pSkeleton;
	spAnimationState* m_pState;
	float* m_pWorldVertices;

public:
	CBasic();
	virtual ~CBasic();

	virtual void Initialize();

	virtual void Update();
	virtual void Render();
};

CBasic::CBasic()
{
	gam_iWidth = 800;
	gam_iHeight = 600;

	m_pWorldVertices = new float[SPINE_MESH_VERTEX_COUNT_MAX];

	_pRenderer = &Renderer;
}

CBasic::~CBasic()
{
}

void CBasic::Initialize()
{
	glewInit();

	spBone_setYDown(true);

	spAtlas* pAtlas = spAtlas_createFromFile("skeleton.atlas", NULL);
	spSkeletonJson* pJson = spSkeletonJson_create(pAtlas);
	spSkeletonData* pSkeletonData = spSkeletonJson_readSkeletonDataFile(pJson, "skeleton.json");
	m_pSkeleton = spSkeleton_create(pSkeletonData);

	spAnimationStateData* pStateData = spAnimationStateData_create(pSkeletonData);
	m_pState = spAnimationState_create(pStateData);
	spAnimationState_setAnimationByName(m_pState, 0, "animation", true);

	// Debug print information about the spine data
	printf("Bones count: %d\n", m_pSkeleton->bonesCount);
	for(int i=0; i<m_pSkeleton->bonesCount; i++) {
		spBone* pBone = m_pSkeleton->bones[i];
		printf("  bone[%d] = { \"%s\", x: %f, y: %f, rotation: %f }\n", i, pBone->data->name, pBone->x, pBone->y, pBone->rotation);
	}
	printf("Slots count: %d\n", m_pSkeleton->slotsCount);
	for(int i=0; i<m_pSkeleton->slotsCount; i++) {
		spSlot* pSlot = m_pSkeleton->slots[i];
		printf("  slot[%d] = { \"%s\", bone: \"%s\" }\n", i, pSlot->data->name, pSlot->bone->data->name);
	}
	printf("Animations count: %d\n", pSkeletonData->animationsCount);
	for(int i=0; i<pSkeletonData->animationsCount; i++) {
		spAnimation* pAnim = pSkeletonData->animations[i];
		printf("  anim[%d] = { \"%s\", duration: %f, timelines: %d }\n", i, pAnim->name, pAnim->duration, pAnim->timelinesCount);
	}

	Window.SetTitle("Example 03: Spine");

	CGame::Initialize();
}

void CBasic::Update()
{
	if(Input.IsKeyDown(MKEY_ESCAPE)) {
		Exit();
	}

	float fDelta = 0.01f;

	spSkeleton_update(m_pSkeleton, fDelta);
	spAnimationState_update(m_pState, fDelta);
	spAnimationState_apply(m_pState, m_pSkeleton);
	spSkeleton_updateWorldTransform(m_pSkeleton);

	CGame::Update();
}

void CBasic::Render()
{
	Renderer.SetColor(COL_BLACK | MRAG_ALPHA_OPAQUE);
	Renderer.Clear();

	Renderer.SetColor(COL_GREEN | MRAG_ALPHA_OPAQUE);
	Vector2f vOffset = Vector2f(200, 200);
	Renderer.PutRectangle(CRectangle(vOffset, Vector2f(200, 200)));

	SDLVertex vertices[4];
	CStackArray<SDLVertex> saVertices;

	CTexture* pTexture = NULL;

	Renderer.SetColor(COL_RED | MRAG_ALPHA_OPAQUE);
  for(int i=0; i<m_pSkeleton->slotsCount; i++) {
		spSlot* pSlot = m_pSkeleton->slots[i];
		spAttachment* pAttachment = pSlot->attachment;
		if(!pAttachment) {
			continue;
		}

		//TODO: Blend modes

		if(pAttachment->type == SP_ATTACHMENT_REGION) {
			spRegionAttachment* pRegionAttachment = (spRegionAttachment*)pAttachment;
			pTexture = (CTexture*)((spAtlasRegion*)pRegionAttachment->rendererObject)->page->rendererObject;
			spRegionAttachment_computeWorldVertices(pRegionAttachment, pSlot->bone, m_pWorldVertices);

			unsigned char r = static_cast<unsigned char>(m_pSkeleton->r * pSlot->r * 255);
			unsigned char g = static_cast<unsigned char>(m_pSkeleton->g * pSlot->g * 255);
			unsigned char b = static_cast<unsigned char>(m_pSkeleton->b * pSlot->b * 255);
			unsigned char a = static_cast<unsigned char>(m_pSkeleton->a * pSlot->a * 255);

			vertices[0].colColor = MRAG_COLOR_RGBA(r, g, b, a);
			vertices[0].vPosition = Vector2f(m_pWorldVertices[SP_VERTEX_X1], m_pWorldVertices[SP_VERTEX_Y1]);
			vertices[0].vTexCoords = Vector2f(pRegionAttachment->uvs[SP_VERTEX_X1] * pTexture->tex_iWidth, pRegionAttachment->uvs[SP_VERTEX_Y1] * pTexture->tex_iHeight);

			vertices[1].colColor = MRAG_COLOR_RGBA(r, g, b, a);
			vertices[1].vPosition = Vector2f(m_pWorldVertices[SP_VERTEX_X2], m_pWorldVertices[SP_VERTEX_Y2]);
			vertices[1].vTexCoords = Vector2f(pRegionAttachment->uvs[SP_VERTEX_X2] * pTexture->tex_iWidth, pRegionAttachment->uvs[SP_VERTEX_Y2] * pTexture->tex_iHeight);

			vertices[2].colColor = MRAG_COLOR_RGBA(r, g, b, a);
			vertices[2].vPosition = Vector2f(m_pWorldVertices[SP_VERTEX_X3], m_pWorldVertices[SP_VERTEX_Y3]);
			vertices[2].vTexCoords = Vector2f(pRegionAttachment->uvs[SP_VERTEX_X3] * pTexture->tex_iWidth, pRegionAttachment->uvs[SP_VERTEX_Y3] * pTexture->tex_iHeight);

			vertices[3].colColor = MRAG_COLOR_RGBA(r, g, b, a);
			vertices[3].vPosition = Vector2f(m_pWorldVertices[SP_VERTEX_X4], m_pWorldVertices[SP_VERTEX_Y4]);
			vertices[3].vTexCoords = Vector2f(pRegionAttachment->uvs[SP_VERTEX_X4] * pTexture->tex_iWidth, pRegionAttachment->uvs[SP_VERTEX_Y4] * pTexture->tex_iHeight);

			saVertices.Push() = vertices[0];
			saVertices.Push() = vertices[1];
			saVertices.Push() = vertices[2];
			saVertices.Push() = vertices[0];
			saVertices.Push() = vertices[2];
			saVertices.Push() = vertices[3];

		} else if(pAttachment->type == SP_ATTACHMENT_MESH) {
			spMeshAttachment* pMesh = (spMeshAttachment*)pAttachment;
			if(pMesh->verticesCount > SPINE_MESH_VERTEX_COUNT_MAX) {
				continue;
			}
			pTexture = (CTexture*)((spAtlasRegion*)pMesh->rendererObject)->page->rendererObject;
			spMeshAttachment_computeWorldVertices(pMesh, pSlot, m_pWorldVertices);

			unsigned char r = static_cast<unsigned char>(m_pSkeleton->r * pSlot->r * 255);
			unsigned char g = static_cast<unsigned char>(m_pSkeleton->g * pSlot->g * 255);
			unsigned char b = static_cast<unsigned char>(m_pSkeleton->b * pSlot->b * 255);
			unsigned char a = static_cast<unsigned char>(m_pSkeleton->a * pSlot->a * 255);

			SDLVertex v;
			v.colColor = MRAG_COLOR_RGBA(r, g, b, a);
			for(int j=0; j<pMesh->trianglesCount; j++) {
				int iIndex = pMesh->triangles[j] << 1;
				v.vPosition = Vector2f(m_pWorldVertices[iIndex], m_pWorldVertices[iIndex + 1]);
				v.vTexCoords = Vector2f(pMesh->uvs[iIndex] * pTexture->tex_iWidth, pMesh->uvs[iIndex + 1] * pTexture->tex_iHeight);
				saVertices.Push() = v;
			}

		} else if(pAttachment->type == SP_ATTACHMENT_SKINNED_MESH) {
			spSkinnedMeshAttachment* pMesh = (spSkinnedMeshAttachment*)pAttachment;
			if(pMesh->uvsCount > SPINE_MESH_VERTEX_COUNT_MAX) {
				continue;
			}
			pTexture = (CTexture*)((spAtlasRegion*)pMesh->rendererObject)->page->rendererObject;
			spSkinnedMeshAttachment_computeWorldVertices(pMesh, pSlot, m_pWorldVertices);

			unsigned char r = static_cast<unsigned char>(m_pSkeleton->r * pSlot->r * 255);
			unsigned char g = static_cast<unsigned char>(m_pSkeleton->g * pSlot->g * 255);
			unsigned char b = static_cast<unsigned char>(m_pSkeleton->b * pSlot->b * 255);
			unsigned char a = static_cast<unsigned char>(m_pSkeleton->a * pSlot->a * 255);

			SDLVertex v;
			v.colColor = MRAG_COLOR_RGBA(r, g, b, a);
			for(int j=0; j<pMesh->trianglesCount; j++) {
				int iIndex = pMesh->triangles[j] << 1;
				v.vPosition = Vector2f(m_pWorldVertices[iIndex], m_pWorldVertices[iIndex + 1]);
				v.vTexCoords = Vector2f(pMesh->uvs[iIndex] * pTexture->tex_iWidth, pMesh->uvs[iIndex + 1] * pTexture->tex_iHeight);
				saVertices.Push() = v;
			}
		}
  }

  if(pTexture != NULL) {
		glUseProgramObjectARB(0);
		glPushMatrix();
		glTranslatef(300, 300, 0);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		SDL_GL_BindTexture(pTexture->tex_pTexture, NULL, NULL);

		int ctVertices = saVertices.Count();
		unsigned int* aIndices = new unsigned int[ctVertices];
		Vector2f* aPositions = new Vector2f[ctVertices];
		Vector2f* aTexCoords = new Vector2f[ctVertices];
		COLOR* aColors = new COLOR[ctVertices];

		for(int i=0; i<ctVertices; i++) {
			SDLVertex &v = saVertices[i];
			aIndices[i] = i;
			aPositions[i] = v.vPosition;
			aTexCoords[i] = v.vTexCoords;
			aColors[i] = v.colColor;
		}

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(2, GL_FLOAT, 0, aPositions);
		glTexCoordPointer(2, GL_FLOAT, 0, aTexCoords);
		glColorPointer(4, GL_UNSIGNED_BYTE, 0, aColors);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDrawElements(GL_TRIANGLES, ctVertices, GL_UNSIGNED_INT, aIndices);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

		SDL_GL_UnbindTexture(pTexture->tex_pTexture);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glDisable(GL_BLEND);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glPopMatrix();

		delete[] aIndices;
		delete[] aPositions;
		delete[] aTexCoords;
		delete[] aColors;
  }

  //Renderer.PutTexture(*pTexture, 0, 0);
	/*for(int i=0; i<m_pSkeleton->bonesCount; i++) {
		spBone* pBone = m_pSkeleton->bones[i];

		float fRot = mthToRadians(pBone->rotation);

		Vector2f vSrc = Vector2f(pBone->x, pBone->y);
		Vector2f vDest = vSrc + Vector2f(cosf(fRot), sinf(fRot)) * 40.0f;

		Renderer.PutLine(vOffset + vSrc, vOffset + vDest);
	}*/

	CGame::Render();
}

int main()
{
	FindExampleContentPath();

	CBasic game;
	game.Run();

	return 0;
}
