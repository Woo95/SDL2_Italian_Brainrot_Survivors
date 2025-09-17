#pragma once

#include "Enemy.h"

class CSkeletonAngel : public CEnemy
{
public:
	CSkeletonAngel();
	virtual ~CSkeletonAngel();

public:
	virtual bool Init() final;

private:
	virtual void Release() final;
};