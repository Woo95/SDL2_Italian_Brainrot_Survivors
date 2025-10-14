#include "Enemy.h"
#include "Gem.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"
#include "../../Scene/Scene.h"
#include "../../Manager/Data/Resource/AssetManager.h"
#include "../../Manager/Data/Resource/SoundManager.h"

CEnemy::CEnemy()
{
}

CEnemy::~CEnemy()
{
}

bool CEnemy::Init()
{
	mChase = AllocateComponent<CChaseComponent, 50>("Chase_Enemy");
	mRootComponent->AddChild(mChase);

	mRigidbody = AllocateComponent<CRigidbody>("Rigidbody_Enemy");
	mRootComponent->AddChild(mRigidbody);

	mChase->SetSpeed(mStatus->GetMoveSpeed());

	return CObject::Init();
}

void CEnemy::Update(float deltaTime)
{
	CObject::Update(deltaTime);

	if (mChase->GetFacingDir().x < 0)
	{
		mSprite->SetFlip(SDL_FLIP_NONE);
	}
	else if (mChase->GetFacingDir().x > 0)
	{
		mSprite->SetFlip(SDL_FLIP_HORIZONTAL);
	}

	TakeDamage(deltaTime * 20.0f);
	if (mIsDead && mSprite->GetAnimation()->IsPlayedOnce())
	{
		Destroy();
		if (Chance(0.75f))
			DropGem();
	}
}

void CEnemy::OnHit(CCollider* self, CCollider* other)
{
}

void CEnemy::TakeDamage(float amount)
{
	CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_EnemyHit")->Play();
	mStatus->AddHP(-amount);

	if (mStatus->GetHP() <= 0.0f)
	{
		mHitbox->Disable();
		mSprite->GetAnimation()->SetState(EAnimationState::DEAD);
		mIsDead = true;
	}
}

void CEnemy::DropGem()
{
	CGem* gem = GetScene()->InstantiateObject<CGem, 50>("Object_Gem", ELayer::Type::OBJECT);
	gem->GetTransform()->SetWorldPos(GetTransform()->GetWorldPos());
}