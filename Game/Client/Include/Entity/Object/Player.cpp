#include "Player.h"
#include "../Component/AllComponents.h"
#include "../../Core/Input.h"

CPlayer::CPlayer() :
	mMovement(nullptr),
	mSprite(nullptr),
	mRigidbody(nullptr),
	mInput(nullptr)
{
}

CPlayer::~CPlayer()
{
	mInput->DeleteFunctionFromBinder("W_MoveUp",    this);
	mInput->DeleteFunctionFromBinder("A_MoveLeft",  this);
	mInput->DeleteFunctionFromBinder("S_MoveDown",  this);
	mInput->DeleteFunctionFromBinder("D_MoveRight", this);

	mInput->DeleteFunctionFromBinder("UP_MoveUp",       this);
	mInput->DeleteFunctionFromBinder("DOWN_MoveDown",   this);
	mInput->DeleteFunctionFromBinder("LEFT_MoveLeft",   this);
	mInput->DeleteFunctionFromBinder("RIGHT_MoveRight", this);
}

bool CPlayer::Init()
{
	BindInput();

	return CObject::Init();
}

void CPlayer::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CPlayer>(this);
}

void CPlayer::BindInput()
{
	mInput = AllocateComponent<CInputComponent>("Input_Player");

	mInput->AddFunctionToBinder("W_MoveUp",    this, [this]() { MoveDir(FVector2D::UP);    });
	mInput->AddFunctionToBinder("A_MoveLeft",  this, [this]() { MoveDir(FVector2D::LEFT);  });
	mInput->AddFunctionToBinder("S_MoveDown",  this, [this]() { MoveDir(FVector2D::DOWN);  });
	mInput->AddFunctionToBinder("D_MoveRight", this, [this]() { MoveDir(FVector2D::RIGHT); });

	mInput->AddInputToBinder("W_MoveUp",    SDL_SCANCODE_W, EKey::State::HOLD);
	mInput->AddInputToBinder("A_MoveLeft",  SDL_SCANCODE_A, EKey::State::HOLD);
	mInput->AddInputToBinder("S_MoveDown",  SDL_SCANCODE_S, EKey::State::HOLD);
	mInput->AddInputToBinder("D_MoveRight", SDL_SCANCODE_D, EKey::State::HOLD);


	mInput->AddFunctionToBinder("UP_MoveUp",       this, [this]() { MoveDir(FVector2D::UP);    });
	mInput->AddFunctionToBinder("DOWN_MoveDown",   this, [this]() { MoveDir(FVector2D::DOWN);  });
	mInput->AddFunctionToBinder("LEFT_MoveLeft",   this, [this]() { MoveDir(FVector2D::LEFT);  });
	mInput->AddFunctionToBinder("RIGHT_MoveRight", this, [this]() { MoveDir(FVector2D::RIGHT); });

	mInput->AddInputToBinder("UP_MoveUp",       SDL_SCANCODE_UP,    EKey::State::HOLD);
	mInput->AddInputToBinder("DOWN_MoveDown",   SDL_SCANCODE_DOWN,  EKey::State::HOLD);
	mInput->AddInputToBinder("LEFT_MoveLeft",   SDL_SCANCODE_LEFT,  EKey::State::HOLD);
	mInput->AddInputToBinder("RIGHT_MoveRight", SDL_SCANCODE_RIGHT, EKey::State::HOLD);

	mRootComponent->AddChild(mInput);
}

void CPlayer::MoveDir(const FVector2D& dir)
{
	mMovement->AddMoveDir(dir);

	OnMoveDirChanged(dir);
}