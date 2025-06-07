#pragma once

#include "Object.h"
#include "../../Core/Vector2D.h"

class CPlayer abstract : public CObject
{
public:
	CPlayer();
	virtual ~CPlayer();

protected:
	class CMovementComponent* mMovement;
	class CSpriteComponent* mSprite;

public:
	virtual bool Init() override;

private:
	virtual void Release() = 0;

private:
	void BindInput();
	void MoveDir(const FVector2D& dir);
};