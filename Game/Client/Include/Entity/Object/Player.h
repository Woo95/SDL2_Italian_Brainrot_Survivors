#pragma once

#include "Object.h"
#include "../../Core/Vector2D.h"

class CMovementComponent;
class CSpriteComponent;
class CInputComponent;
class CRigidbody;

class CPlayer abstract : public CObject
{
public:
	CPlayer();
	virtual ~CPlayer();

protected:
	CMovementComponent* mMovement;
	CSpriteComponent* mSprite;
	CInputComponent* mInput;
	CRigidbody* mRigidbody;

public:
	virtual bool Init() override;

private:
	virtual void Release() = 0;
	virtual void OnMoveDirChanged(const FVector2D& dir) = 0;

private:
	void BindInput();
	void MoveDir(const FVector2D& dir);
};