#include "Player.h"
#include "../Component/AllComponents.h"
#include "../../Core/Input.h"

CPlayer::CPlayer() :
	mMovement(nullptr),
	mSprite(nullptr)
{
}

CPlayer::~CPlayer()
{
	CInput* input = CInput::GetInst();

	CInput::GetInst()->DeleteFunctionFromBinder("W_MoveUp",    this);
	CInput::GetInst()->DeleteFunctionFromBinder("A_MoveLeft",  this);
	CInput::GetInst()->DeleteFunctionFromBinder("S_MoveDown",  this);
	CInput::GetInst()->DeleteFunctionFromBinder("D_MoveRight", this);

	CInput::GetInst()->DeleteFunctionFromBinder("UP_MoveUp",       this);
	CInput::GetInst()->DeleteFunctionFromBinder("DOWN_MoveDown",   this);
	CInput::GetInst()->DeleteFunctionFromBinder("LEFT_MoveLeft",   this);
	CInput::GetInst()->DeleteFunctionFromBinder("RIGHT_MoveRight", this);
}

bool CPlayer::Init()
{
	mMovement = AllocateComponent<CMovementComponent>("MovementComponent_Player");

	CCollider* collider = AllocateComponent<CBoxCollider>("BoxCollider_Player");
	collider->GetTransform()->SetWorldScale(50.f, 75.f);
	collider->GetTransform()->SetPivot(0.5f, 0.5f);

	mRootComponent->AddChild(mMovement);
	mRootComponent->AddChild(collider);

	BindInput();

	return CObject::Init();
}

void CPlayer::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CPlayer>(this);
}

void CPlayer::BindInput()
{
	CInput* input = CInput::GetInst();

	input->AddFunctionToBinder("W_MoveUp",    this, [this]() { MoveDir(FVector2D::UP);    });
	input->AddFunctionToBinder("A_MoveLeft",  this, [this]() { MoveDir(FVector2D::LEFT);  });
	input->AddFunctionToBinder("S_MoveDown",  this, [this]() { MoveDir(FVector2D::DOWN);  });
	input->AddFunctionToBinder("D_MoveRight", this, [this]() { MoveDir(FVector2D::RIGHT); });

	input->AddInputToBinder("W_MoveUp",    SDL_SCANCODE_W, EKey::State::HOLD);
	input->AddInputToBinder("A_MoveLeft",  SDL_SCANCODE_A, EKey::State::HOLD);
	input->AddInputToBinder("S_MoveDown",  SDL_SCANCODE_S, EKey::State::HOLD);
	input->AddInputToBinder("D_MoveRight", SDL_SCANCODE_D, EKey::State::HOLD);


	input->AddFunctionToBinder("UP_MoveUp",       this, [this]() { MoveDir(FVector2D::UP);    });
	input->AddFunctionToBinder("DOWN_MoveDown",   this, [this]() { MoveDir(FVector2D::DOWN);  });
	input->AddFunctionToBinder("LEFT_MoveLeft",   this, [this]() { MoveDir(FVector2D::LEFT);  });
	input->AddFunctionToBinder("RIGHT_MoveRight", this, [this]() { MoveDir(FVector2D::RIGHT); });

	input->AddInputToBinder("UP_MoveUp",       SDL_SCANCODE_UP,    EKey::State::HOLD);
	input->AddInputToBinder("DOWN_MoveDown",   SDL_SCANCODE_DOWN,  EKey::State::HOLD);
	input->AddInputToBinder("LEFT_MoveLeft",   SDL_SCANCODE_LEFT,  EKey::State::HOLD);
	input->AddInputToBinder("RIGHT_MoveRight", SDL_SCANCODE_RIGHT, EKey::State::HOLD);

}

void CPlayer::MoveDir(const FVector2D& dir)
{
	mMovement->AddMoveDir(dir);

	if (mSprite)
	{
		if (dir == FVector2D::LEFT)
			mSprite->SetFlip(SDL_FLIP_HORIZONTAL);
		else if (dir == FVector2D::RIGHT)
			mSprite->SetFlip(SDL_FLIP_NONE);
	}
}