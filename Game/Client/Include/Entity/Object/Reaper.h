#pragma once

#include "Enemy.h"

class CReaper : public CEnemy
{
public:
	CReaper();
	virtual ~CReaper();

public:
	virtual bool Init() final;

private:
	virtual void Release() final;
};