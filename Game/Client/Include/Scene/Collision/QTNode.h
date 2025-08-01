#pragma once

#include "../../Core/GameInfo.h"

#define MAX_COLLIDERS_PER_NODE 15
#define MAX_SPLIT 3

class CCollider;
class CCamera;

class CQTNode
{
	friend class CQuadTree;

public:
	CQTNode();
	~CQTNode();

private:
	CCamera* mCamera = nullptr;

	CQTNode* mParent = nullptr;
	CQTNode* mChilds[4] = {};
	std::vector<CCollider*> mColliders;

	SDL_FRect mBoundary = {};

	int mSplitLevel = 0;

public:
	void Update(float deltaTime);
	void Render(SDL_Renderer* renderer);

public:
	bool HasChild();
	bool ShouldSplit();
	void Split();

	bool IsWithinNode(CCollider* collider);
	void AddCollider(CCollider* collider);

	void MoveCollidersToChildren();

	void Clear();
};