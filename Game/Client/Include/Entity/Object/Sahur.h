#pragma once

#include "Player.h"

class CSahur : public CPlayer
{
public:
	CSahur();
	virtual ~CSahur();

public:
	virtual bool Init() final;

private:
	virtual void Release() final;
};