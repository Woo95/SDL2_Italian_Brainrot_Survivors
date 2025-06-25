#pragma once

#include "Player.h"

class CCollider;

class CBananini : public CPlayer
{
public:
	CBananini();
	virtual ~CBananini();

public:
	virtual bool Init() final;

private:
	virtual void Release() final;
	virtual void OnMoveDirChanged(const FVector2D& dir) final;
};