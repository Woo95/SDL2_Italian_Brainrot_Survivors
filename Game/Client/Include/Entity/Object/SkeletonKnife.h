#pragma once

#include "Enemy.h"

class CSkeletonKnife : public CEnemy
{
public:
	CSkeletonKnife();
	virtual ~CSkeletonKnife();

public:
	virtual bool Init() final;

private:
	virtual void Release() final;
};