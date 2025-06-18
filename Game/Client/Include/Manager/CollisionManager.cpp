#include "CollisionManager.h"
#include "../Entity/Component/Collider/BoxCollider.h"
#include "../Entity/Component/Collider/CircleCollider.h"
#include "../Widget/WidgetBase.h"

CCollisionManager* CCollisionManager::mInst = nullptr;

CCollisionManager::CCollisionManager()
{
}

CCollisionManager::~CCollisionManager()
{
	std::unordered_map<std::string, FCollisionProfile*>::iterator iter    = mProfileMap.begin();
	std::unordered_map<std::string, FCollisionProfile*>::iterator iterEnd = mProfileMap.end();

	for (; iter != iterEnd; iter++)
	{
		SAFE_DELETE(iter->second);
	}
}

bool CCollisionManager::Init()
{
	CreateProfile("PlayerHitBox", ECollision::Channel::PLAYER_HITBOX, ECollision::Interaction::BLOCK);
	CreateProfile("PlayerFoot", ECollision::Channel::PLAYER_FOOT, ECollision::Interaction::IGNORE);
	CreateProfile("Environment", ECollision::Channel::ENVIRONMENT, ECollision::Interaction::BLOCK);

	SetCollisionInteraction("PlayerHitBox", ECollision::Channel::ENVIRONMENT, ECollision::Interaction::IGNORE);
	SetCollisionInteraction("PlayerFoot", ECollision::Channel::ENVIRONMENT, ECollision::Interaction::BLOCK);

	return true;
}

bool CCollisionManager::CreateProfile(const std::string& name, ECollision::Channel myChannel, ECollision::Interaction interaction)
{
	if (FindProfile(name))	// exist
		return false;

	mProfileMap[name] = new FCollisionProfile(name, myChannel, interaction);

	return true;
}

bool CCollisionManager::SetCollisionInteraction(const std::string& name, ECollision::Channel otherChannel, ECollision::Interaction interaction)
{
	FCollisionProfile* profile = FindProfile(name);
	if (!profile)
		return false;

	profile->collisionResponses[otherChannel] = interaction;

	return true;
}

FCollisionProfile* CCollisionManager::FindProfile(const std::string& name)
{
	std::unordered_map<std::string, FCollisionProfile*>::iterator iter    = mProfileMap.find(name);
	std::unordered_map<std::string, FCollisionProfile*>::iterator iterEnd = mProfileMap.end();

	if (iter != iterEnd)
		return iter->second;
	else
		return nullptr;
}

bool CCollisionManager::AABBCollision(CBoxCollider* collider1, CBoxCollider* collider2)
{
	const SDL_FRect& box1 = collider1->GetRect();
	const SDL_FRect& box2 = collider2->GetRect();

	if (box1.x + box1.w < box2.x ||
		box1.x > box2.x + box2.w ||
		box1.y + box1.h < box2.y ||
		box1.y > box2.y + box2.h)
	{
		return false;
	}

	FVector2D hitPoint;
	hitPoint.x = (std::max(box1.x, box2.x) + std::min(box1.x + box1.w, box2.x + box2.w)) * 0.5f;
	hitPoint.y = (std::max(box1.y, box2.y) + std::min(box1.y + box1.h, box2.y + box2.h)) * 0.5f;

	collider1->mHitPoint = hitPoint;
	collider2->mHitPoint = hitPoint;

	return true;
}

bool CCollisionManager::CircleCircleCollision(CCircleCollider* collider1, CCircleCollider* collider2)
{
	const FCircle& circle1 = collider1->GetCircle();
	const FCircle& circle2 = collider2->GetCircle();

	float distance  = circle1.center.Distance(circle2.center);
	float sumRadius = circle1.radius + circle2.radius;

	if (distance > sumRadius)
	{
		return false;
	}

	FVector2D hitPoint = (circle1.center + circle2.center) * 0.5f;

	collider1->mHitPoint = hitPoint;
	collider2->mHitPoint = hitPoint;

	return true;
}

bool CCollisionManager::AABBCircleCollision(CBoxCollider* collider1, CCircleCollider* collider2)
{
	const SDL_FRect& box  = collider1->GetRect();
	const FCircle& circle = collider2->GetCircle();

	// 원의 중심에서 사각형 테두리를 기준으로 가장 가까운 점을 찾는다.
	FVector2D closestPointOnBox = circle.center.Clamp(box.x, box.x + box.w, box.y + box.h, box.y);

	// 원의 중심과 그 점의 거리를 찾는다.
	float distance = circle.center.Distance(closestPointOnBox);

	if (circle.radius < distance)
	{
		return false;
	}

	FVector2D hitPoint = closestPointOnBox;

	collider1->mHitPoint = hitPoint;
	collider2->mHitPoint = hitPoint;

	return true;
}

bool CCollisionManager::AABBPointCollision(const SDL_Rect& rect, const FVector2D& point)
{
	if (rect.x + rect.w < point.x ||
	    rect.x > point.x          ||
	    rect.y + rect.h < point.y ||
		rect.y > point.y)
	{
		return false;
	}
	return true;
}

bool CCollisionManager::AABBPointCollision(CBoxCollider* collider, const FVector2D& point)
{
	const SDL_FRect& box = collider->GetRect();

	if (box.x + box.w < point.x ||
	    box.x > point.x         ||
	    box.y + box.h < point.y ||
	    box.y > point.y)
	{
		return false;
	}

	collider->mHitPoint = point;

	return true;
}

bool CCollisionManager::CirclePointCollision(CCircleCollider* collider, const FVector2D& point)
{
	const FCircle& circle = collider->GetCircle();

	if (circle.center.Distance(point) > circle.radius)
	{
		return false;
	}

	collider->mHitPoint = point;

	return true;
}