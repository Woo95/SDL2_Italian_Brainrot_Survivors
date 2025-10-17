#include "Enemy.h"
#include "Player.h"
#include "Gem.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"
#include "../../Scene/Scene.h"
#include "../../Manager/Data/Resource/AssetManager.h"
#include "../../Manager/Data/Resource/SoundManager.h"
#include "../../Scene/PlayScene.h"

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

	mHitbox->AddCallbackFunc<CEnemy>(ECollider::OnCollision::ENTER, this, &CEnemy::OnCollisionEnter);
	mHitbox->AddCallbackFunc<CEnemy>(ECollider::OnCollision::EXIT, this, &CEnemy::OnCollisionExit);

	mChase->SetSpeed(mStatus->GetMoveSpeed());

	return CObject::Init();
}

void CEnemy::Update(float deltaTime)
{
	CObject::Update(deltaTime);

	mInvincibleTimer -= deltaTime;
	if (mInvincibleTimer <= 0.0f)
	{
		mIsInvincible = false;
		mInvincibleTimer = CONST_INVINCIBLE_TIMER;
	}

	if (mTarget)
	{
		// 초당 데미지
		mTarget->TakeDamage(mStatus->GetAttack() * deltaTime);
	}

	if (mChase->GetFacingDir().x < 0)
	{
		mSprite->SetFlip(SDL_FLIP_NONE);
	}
	else if (mChase->GetFacingDir().x > 0)
	{
		mSprite->SetFlip(SDL_FLIP_HORIZONTAL);
	}

	if (mSprite->GetAnimation()->GetState() == EAnimationState::DEAD)
	{
		if (mSprite->GetAnimation()->IsPlayedOnce())
		{
			Destroy();
			if (Chance(0.5f))
				DropGem();
		}
	}
}

void CEnemy::TakeDamage(float amount, bool useInvincibility)
{
	if (useInvincibility && mIsInvincible)
		return;

	CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_Hit")->Play();
	mStatus->AddHP(-amount);

	if (mStatus->GetHP() <= 0.0f)
	{
		((CPlayScene*)mScene)->GetPlayer()->AddKill();
		mSprite->GetAnimation()->SetState(EAnimationState::DEAD);
		mHitbox->Disable();
		mChase->Disable();
	}

	mIsInvincible = true;
}

void CEnemy::DropGem()
{
	CGem* gem = GetScene()->InstantiateObject<CGem, 50>("Object_Gem", ELayer::Type::OBJECT);
	gem->SetExp(mStatus->GetExp());
	gem->GetTransform()->SetWorldPos(GetTransform()->GetWorldPos());
}

void CEnemy::OnCollisionEnter(CCollider* self, CCollider* other)
{
	if (CPlayer* player = dynamic_cast<CPlayer*>(other->GetObject()))
	{
		mTarget = player;
	}
}

void CEnemy::OnCollisionExit(CCollider* self, CCollider* other)
{
	mTarget = nullptr;
}