#pragma once

#include "UserWidget.h"

class COptionPanel : public CUserWidget
{
public:
	COptionPanel();
	virtual ~COptionPanel();

protected:
	virtual void Construct() final;
	virtual void Release() final;
};