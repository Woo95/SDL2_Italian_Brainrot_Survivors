#pragma once

#include "Object.h"

class CMadForest : public CObject
{
public:
	CMadForest();
	virtual ~CMadForest();

public:
	virtual bool Init() final;

private:
	virtual void Release() final;

private:
	void SetEnvObjects();
};