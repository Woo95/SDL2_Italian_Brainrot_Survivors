#include "Enemy.h"
#include "Player.h"
#include "Gem.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"
#include "../../Scene/Scene.h"
#include "../../Manager/Data/Resource/AssetManager.h"
#include "../../Manager/Data/Resource/SoundManager.h"
#include "../../Scene/PlayScene.h"
#include "../../Core/Timer.h"

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

	mHitVfx = AllocateComponent<CVFXComponent, 50>("VFX_Enemy");
	mHitVfx->SetTexture("Texture_VfxAtlas");
	mHitVfx->SetAnimation("EnemyHitVFX");
	mHitVfx->GetAnimation()->SetState(EAnimationState::VFX);
	mHitVfx->GetTransform()->SetWorldScale(25.0f, 36.0f);
	mHitVfx->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mHitVfx);

	mRigidbody = AllocateComponent<CRigidbody>("Rigidbody_Enemy");
	mRootComponent->AddChild(mRigidbody);

	mHitbox->AddCallbackFunc<CEnemy>(ECollider::OnCollision::ENTER, this, &CEnemy::OnCollisionEnter);
	mHitbox->AddCallbackFunc<CEnemy>(ECollider::OnCollision::STAY, this, &CEnemy::OnCollisionStay);
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

	// UpdateFacingDir
	if (mChase->GetFacingDir().x < 0)
	{
		mSprite->SetFlip(SDL_FLIP_NONE);
	}
	else if (mChase->GetFacingDir().x > 0)
	{
		mSprite->SetFlip(SDL_FLIP_HORIZONTAL);
	}

	// UpdateDeadState
	if (mSprite->GetAnimation()->GetState() == EAnimationState::DEAD)
	{
		if (mSprite->GetAnimation()->IsPlayedOnce())
		{
			if (Chance(mGemSpawnRate))
			{
				CGem* gem = GetScene()->InstantiateObject<CGem, 50>("Object_Gem", ELayer::Type::OBJECT);
				gem->GetTransform()->SetWorldPos(GetTransform()->GetWorldPos());
				gem->SetExp(mStatus->GetExp());
				switch (mGemType)
				{
				case EGem::BLUE:
					gem->GetSprite()->SetFrame("BlueGem");
					break;
				case EGem::RED:
					gem->GetSprite()->SetFrame("RedGem");
					break;
				}
			}
			Destroy();
		}
	}
}

void CEnemy::TakeDamage(float amount, bool useInvincibility)
{
	if (useInvincibility && mIsInvincible)
		return;

	CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_EnemyHit")->Play();
	mHitVfx->PlayVFX(mHitbox->GetHitPoint());
	mIsInvincible = true;

	mStatus->AddHP(-amount);
	if (mStatus->GetHP() <= 0.0f)
	{
		((CPlayScene*)mScene)->GetPlayer()->AddKill();
		mSprite->GetAnimation()->SetState(EAnimationState::DEAD);
		mHitbox->Disable();
		mChase->Disable();
	}
}

void CEnemy::OnCollisionEnter(CCollider* self, CCollider* other)
{
	mTarget = dynamic_cast<CPlayer*>(other->GetObject());
}

void CEnemy::OnCollisionStay(CCollider* self, CCollider* other)
{
	if (!mTarget)
		return;

	mTarget->TakeDamage(mStatus->GetAttack() * CTimer::GetInst()->GetDeltaTime());
}

void CEnemy::OnCollisionExit(CCollider* self, CCollider* other)
{
	if (!mTarget)
		return;

	mTarget = nullptr;
}