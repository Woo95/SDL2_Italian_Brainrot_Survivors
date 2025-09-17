#pragma once

#include "Enemy.h"

class CSkeletonMad : public CEnemy
{
public:
	CSkeletonMad();
	virtual ~CSkeletonMad();

public:
	virtual bool Init() final;

private:
	virtual void Release() final;
};