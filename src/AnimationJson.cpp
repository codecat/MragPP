#include "StdH.h"
#include "AnimationJson.h"
#include "Game.h"

#include "spine/spine.h"
#include "spine/extension.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>

#ifndef SPINE_MESH_VERTEX_COUNT_MAX
#define SPINE_MESH_VERTEX_COUNT_MAX 1000
#endif

using namespace Scratch;

MRAGPP_NAMESPACE_BEGIN;

static CRenderer* __pRenderer = NULL;

struct SDLVertex
{
	COLOR colColor;
	Vector2f vPosition;
	Vector2f vTexCoords;
};

CAnimationJson::CAnimationJson()
{
	ani_pSkeleton = NULL;
	ani_pSkeletonData = NULL;
	ani_pState = NULL;
	ani_pWorldVertices = new float[SPINE_MESH_VERTEX_COUNT_MAX];
}

CAnimationJson::~CAnimationJson()
{
	if(ani_pSkeleton != NULL) {
		spSkeleton_dispose(ani_pSkeleton);
	}
	if(ani_pSkeletonData != NULL) {
		spSkeletonData_dispose(ani_pSkeletonData);
	}
	if(ani_pState != NULL) {
		spAnimationState_dispose(ani_pState);
	}
	delete[] ani_pWorldVertices;
}

void CAnimationJson::Load(CGame* pGame, const char* szAtlas, const char* szJson)
{
	__pRenderer = &pGame->Renderer;

	spBone_setYDown(true);

	spAtlas* pAtlas = spAtlas_createFromFile(szAtlas, NULL);
	spSkeletonJson* pJson = spSkeletonJson_create(pAtlas);
	ani_pSkeletonData = spSkeletonJson_readSkeletonDataFile(pJson, szJson);
	ani_pSkeleton = spSkeleton_create(ani_pSkeletonData);

	spSkeletonJson_dispose(pJson);

	spAnimationStateData* pStateData = spAnimationStateData_create(ani_pSkeletonData);
	ani_pState = spAnimationState_create(pStateData);
}

void CAnimationJson::DumpInfo()
{
	printf("Bones count: %d\n", ani_pSkeleton->bonesCount);
	for(int i=0; i<ani_pSkeleton->bonesCount; i++) {
		spBone* pBone = ani_pSkeleton->bones[i];
		printf("  bone[%d] = { \"%s\", x: %f, y: %f, rotation: %f }\n", i, pBone->data->name, pBone->x, pBone->y, pBone->rotation);
	}
	printf("Slots count: %d\n", ani_pSkeleton->slotsCount);
	for(int i=0; i<ani_pSkeleton->slotsCount; i++) {
		spSlot* pSlot = ani_pSkeleton->slots[i];
		printf("  slot[%d] = { \"%s\", bone: \"%s\" }\n", i, pSlot->data->name, pSlot->bone->data->name);
	}
	printf("Animations count: %d\n", ani_pSkeletonData->animationsCount);
	for(int i=0; i<ani_pSkeletonData->animationsCount; i++) {
		spAnimation* pAnim = ani_pSkeletonData->animations[i];
		printf("  anim[%d] = { \"%s\", duration: %f, timelines: %d }\n", i, pAnim->name, pAnim->duration, pAnim->timelinesCount);
	}
}

void CAnimationJson::SetAnimation(const char* szName, bool bLooping)
{
	spAnimationState_setAnimationByName(ani_pState, 0, szName, bLooping ? 1 : 0);
}

void CAnimationJson::Update(float fDeltatime)
{
	spSkeleton_update(ani_pSkeleton, fDeltatime);
	spAnimationState_update(ani_pState, fDeltatime);
	spAnimationState_apply(ani_pState, ani_pSkeleton);
	spSkeleton_updateWorldTransform(ani_pSkeleton);
}

void CAnimationJson::Render(CRenderer &rend, const Vector2f &vPos)
{
	Render(rend, vPos, Vector2f(1, 1), 0);
}

void CAnimationJson::Render(CRenderer &rend, const Vector2f &vPos, float fRotation)
{
	Render(rend, vPos, Vector2f(1, 1), fRotation);
}

void CAnimationJson::Render(CRenderer &rend, const Vector2f &vPos, const Vector2f &vScale)
{
	Render(rend, vPos, vScale, 0);
}

void CAnimationJson::Render(CRenderer &rend, const Vector2f &vPos, const Vector2f &vScale, float fRotation)
{
	SDLVertex vertices[4];
	CStackArray<SDLVertex> saVertices;

	CTexture* pTexture = NULL;

	for(int i=0; i<ani_pSkeleton->slotsCount; i++) {
		spSlot* pSlot = ani_pSkeleton->slots[i];
		spAttachment* pAttachment = pSlot->attachment;
		if(!pAttachment) {
			continue;
		}

		//TODO: Blend modes

		if(pAttachment->type == SP_ATTACHMENT_REGION) {
			spRegionAttachment* pRegionAttachment = (spRegionAttachment*)pAttachment;
			pTexture = (CTexture*)((spAtlasRegion*)pRegionAttachment->rendererObject)->page->rendererObject;
			spRegionAttachment_computeWorldVertices(pRegionAttachment, pSlot->bone, ani_pWorldVertices);

			unsigned char r = static_cast<unsigned char>(ani_pSkeleton->r * pSlot->r * 255);
			unsigned char g = static_cast<unsigned char>(ani_pSkeleton->g * pSlot->g * 255);
			unsigned char b = static_cast<unsigned char>(ani_pSkeleton->b * pSlot->b * 255);
			unsigned char a = static_cast<unsigned char>(ani_pSkeleton->a * pSlot->a * 255);

			vertices[0].colColor = MRAG_COLOR_RGBA(r, g, b, a);
			vertices[0].vPosition = Vector2f(ani_pWorldVertices[SP_VERTEX_X1], ani_pWorldVertices[SP_VERTEX_Y1]);
			vertices[0].vTexCoords = Vector2f(pRegionAttachment->uvs[SP_VERTEX_X1] * pTexture->tex_iWidth, pRegionAttachment->uvs[SP_VERTEX_Y1] * pTexture->tex_iHeight);

			vertices[1].colColor = MRAG_COLOR_RGBA(r, g, b, a);
			vertices[1].vPosition = Vector2f(ani_pWorldVertices[SP_VERTEX_X2], ani_pWorldVertices[SP_VERTEX_Y2]);
			vertices[1].vTexCoords = Vector2f(pRegionAttachment->uvs[SP_VERTEX_X2] * pTexture->tex_iWidth, pRegionAttachment->uvs[SP_VERTEX_Y2] * pTexture->tex_iHeight);

			vertices[2].colColor = MRAG_COLOR_RGBA(r, g, b, a);
			vertices[2].vPosition = Vector2f(ani_pWorldVertices[SP_VERTEX_X3], ani_pWorldVertices[SP_VERTEX_Y3]);
			vertices[2].vTexCoords = Vector2f(pRegionAttachment->uvs[SP_VERTEX_X3] * pTexture->tex_iWidth, pRegionAttachment->uvs[SP_VERTEX_Y3] * pTexture->tex_iHeight);

			vertices[3].colColor = MRAG_COLOR_RGBA(r, g, b, a);
			vertices[3].vPosition = Vector2f(ani_pWorldVertices[SP_VERTEX_X4], ani_pWorldVertices[SP_VERTEX_Y4]);
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
			spMeshAttachment_computeWorldVertices(pMesh, pSlot, ani_pWorldVertices);

			unsigned char r = static_cast<unsigned char>(ani_pSkeleton->r * pSlot->r * 255);
			unsigned char g = static_cast<unsigned char>(ani_pSkeleton->g * pSlot->g * 255);
			unsigned char b = static_cast<unsigned char>(ani_pSkeleton->b * pSlot->b * 255);
			unsigned char a = static_cast<unsigned char>(ani_pSkeleton->a * pSlot->a * 255);

			SDLVertex v;
			v.colColor = MRAG_COLOR_RGBA(r, g, b, a);
			for(int j=0; j<pMesh->trianglesCount; j++) {
				int iIndex = pMesh->triangles[j] << 1;
				v.vPosition = Vector2f(ani_pWorldVertices[iIndex], ani_pWorldVertices[iIndex + 1]);
				v.vTexCoords = Vector2f(pMesh->uvs[iIndex] * pTexture->tex_iWidth, pMesh->uvs[iIndex + 1] * pTexture->tex_iHeight);
				saVertices.Push() = v;
			}

		} else if(pAttachment->type == SP_ATTACHMENT_SKINNED_MESH) {
			spSkinnedMeshAttachment* pMesh = (spSkinnedMeshAttachment*)pAttachment;
			if(pMesh->uvsCount > SPINE_MESH_VERTEX_COUNT_MAX) {
				continue;
			}
			pTexture = (CTexture*)((spAtlasRegion*)pMesh->rendererObject)->page->rendererObject;
			spSkinnedMeshAttachment_computeWorldVertices(pMesh, pSlot, ani_pWorldVertices);

			unsigned char r = static_cast<unsigned char>(ani_pSkeleton->r * pSlot->r * 255);
			unsigned char g = static_cast<unsigned char>(ani_pSkeleton->g * pSlot->g * 255);
			unsigned char b = static_cast<unsigned char>(ani_pSkeleton->b * pSlot->b * 255);
			unsigned char a = static_cast<unsigned char>(ani_pSkeleton->a * pSlot->a * 255);

			SDLVertex v;
			v.colColor = MRAG_COLOR_RGBA(r, g, b, a);
			for(int j=0; j<pMesh->trianglesCount; j++) {
				int iIndex = pMesh->triangles[j] << 1;
				v.vPosition = Vector2f(ani_pWorldVertices[iIndex], ani_pWorldVertices[iIndex + 1]);
				v.vTexCoords = Vector2f(pMesh->uvs[iIndex] * pTexture->tex_iWidth, pMesh->uvs[iIndex + 1] * pTexture->tex_iHeight);
				saVertices.Push() = v;
			}
		}
	}

	if(pTexture != NULL) {
		glUseProgramObjectARB(0);
		glPushMatrix();

		glTranslatef(vPos(1), vPos(2), 0);
		glRotatef(fRotation, 0, 0, 0);
		glScalef(vScale(1), vScale(2), 0);

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
		glPopMatrix();

		delete[] aIndices;
		delete[] aPositions;
		delete[] aTexCoords;
		delete[] aColors;
	}
}

MRAGPP_NAMESPACE_END;

// Functions that have to be implemented for the spine-c runtime
void _spAtlasPage_createTexture(spAtlasPage* self, const char* path)
{
	Mragpp::CTexture* pTexture = new Mragpp::CTexture();
	pTexture->Load(*Mragpp::__pRenderer, path);
	self->rendererObject = (void*)pTexture;
	self->width = pTexture->tex_iWidth;
	self->height = pTexture->tex_iHeight;
}

void _spAtlasPage_disposeTexture(spAtlasPage* self)
{
	delete (Mragpp::CTexture*)self->rendererObject;
}

char* _spUtil_readFile(const char* path, int* length)
{
	return _readFile(path, length);
}
