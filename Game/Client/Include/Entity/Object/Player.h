#pragma once

#include "Object.h"
#include "../../Core/Vector2D.h"

class CPlayer : public CObject
{
public:
	CPlayer();
	virtual ~CPlayer();

private:
	class CMovementComponent* mMovement;
	class CSpriteComponent* mSprite;

public:
	virtual bool Init();

private:
	virtual void Release() final;

private:
	void BindInput();
	void MoveDir(const FVector2D& dir);
};