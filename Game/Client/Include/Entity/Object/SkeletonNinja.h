#pragma once

#include "Enemy.h"

class CSkeletonNinja : public CEnemy
{
public:
	CSkeletonNinja();
	virtual ~CSkeletonNinja();

public:
	virtual bool Init() final;

private:
	virtual void Release() final;
};