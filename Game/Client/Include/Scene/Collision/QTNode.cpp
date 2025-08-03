#include "QTNode.h"
#include "../Camera.h"
#include "../../Entity/Component/Collider/BoxCollider.h"
#include "../../Entity/Component/Collider/CircleCollider.h"
#include "../../Manager/SceneManager.h"
#include "../Scene.h"
#include "../../Scene/Collision/SceneCollision.h"

CQTNode::CQTNode() :
	mCamera(nullptr),
	mParent(nullptr),
	mChilds({}),
	mBoundary({})
{
}

CQTNode::~CQTNode()
{
}

void CQTNode::Update(float deltaTime)
{
	if (HasChild())
	{
		for (int i = 0; i < 4; i++)
		{
			mChilds[i]->Update(deltaTime);
		}
	}
	else
	{
		size_t size = mColliders.size();
		if (size >= 2)
		{
			CSceneCollision* sceneCollision = CSceneManager::GetInst()->GetCurrentScene()->GetCollision();

			for (size_t i = 0; i < size; i++)
			{
				for (size_t j = i + 1; j < size; j++)
				{
					FCollisionProfile* profile1 = mColliders[i]->GetProfile();
					FCollisionProfile* profile2 = mColliders[j]->GetProfile();

					if (profile1->collisionResponses[profile2->channel] == ECollision::Interaction::IGNORE ||
						profile2->collisionResponses[profile1->channel] == ECollision::Interaction::IGNORE)
					{
						continue;
					}
					sceneCollision->HandleCollision(mColliders[i], mColliders[j]);
				}
			}
		}
	}
}

void CQTNode::Render(SDL_Renderer* renderer)
{
#ifdef _DEBUG	
	// 렌더 색상 설정
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// 카메라가 있을 경우, 카메라 좌표계를 반영한 렌더링 좌표로 변환
	if (mCamera)
	{
		const FVector2D renderPos = mCamera->GetRenderPos(FVector2D(mBoundary.x, mBoundary.y));

		mBoundary = { renderPos.x, renderPos.y, mBoundary.w, mBoundary.h };
	}

	// 사각형 그리기
	SDL_RenderDrawRectF(renderer, &mBoundary);

	if (HasChild())
	{
		for (int i = 0; i < 4; i++)
		{
			mChilds[i]->Render(renderer);
		}
	}
#endif
}

bool CQTNode::HasChild()
{
	return mChilds[0] != nullptr;
}

bool CQTNode::ShouldSplit()
{
	return mColliders.size() > MAX_COLLIDERS_PER_NODE && mSplitLevel < MAX_SPLIT;
}

void CQTNode::Split()
{
	float halfW = mBoundary.w * 0.5f;
	float halfH = mBoundary.h * 0.5f;

	float x[2] = { mBoundary.x, mBoundary.x + halfW };
	float y[2] = { mBoundary.y, mBoundary.y + halfH };

	for (int i = 0; i < 4; i++)
	{
		mChilds[i] = CMemoryPoolManager::GetInst()->Allocate<CQTNode>();

		mChilds[i]->mParent     = this;
		mChilds[i]->mBoundary   = { x[i % 2], y[i / 2], halfW, halfH };
		mChilds[i]->mSplitLevel = mSplitLevel + 1;
		mChilds[i]->mCamera     = mCamera;
	}
}

bool CQTNode::IsWithinNode(CCollider* collider)
{
	if (collider->GetColliderType() == ECollider::Type::BOX)
	{
		const SDL_FRect& box1 = mBoundary;
		const SDL_FRect& box2 = ((CBoxCollider*)collider)->GetRect();

		if (box1.x + box1.w < box2.x ||
			box1.x > box2.x + box2.w ||
			box1.y + box1.h < box2.y ||
			box1.y > box2.y + box2.h)
		{
			return false;
		}
		return true;
	}
	else if (collider->GetColliderType() == ECollider::Type::CIRCLE)
	{
		const SDL_FRect& box  = mBoundary;
		const FCircle& circle = ((CCircleCollider*)collider)->GetCircle();

		FVector2D closestPointOnBox = circle.center.Clamp(box.x, box.x + box.w, box.y + box.h, box.y);

		float distance = circle.center.Distance(closestPointOnBox);

		if (circle.radius < distance)
		{
			return false;
		}
		return true;
	}
	return false;
}

void CQTNode::AddCollider(CCollider* collider)
{
	if (!IsWithinNode(collider))
		return;

	if (HasChild())
	{
		for (int i = 0; i < 4; i++)
		{
			if (mChilds[i]->IsWithinNode(collider))
			{
				mChilds[i]->AddCollider(collider);
			}
		}
	}
	else
	{
		mColliders.emplace_back(collider);

		if (ShouldSplit())
		{
			Split();

			MoveCollidersToChildren();
		}
	}
}

void CQTNode::MoveCollidersToChildren()
{
	for (size_t i = mColliders.size(); i > 0; i--)
	{
		CCollider* collider = mColliders[i - 1];
		for (int j = 0; j < 4; j++)
		{
			if (mChilds[j]->IsWithinNode(collider))
			{
				mChilds[j]->AddCollider(collider);
			}
		}
		mColliders.pop_back();
	}
	mColliders.clear();
}

void CQTNode::Clear()
{
	if (HasChild())
	{
		for (int i = 0; i < 4; i++)
		{
			mChilds[i]->Clear();
			mChilds[i] = nullptr;
		}
	}
	mColliders.clear();

	if (mParent)
		CMemoryPoolManager::GetInst()->Deallocate<CQTNode>(this);
}