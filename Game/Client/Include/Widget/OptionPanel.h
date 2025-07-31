#pragma once

#include "UserWidget.h"

class COptionPanel : public CUserWidget
{
public:
	COptionPanel();
	virtual ~COptionPanel();

protected:
	virtual void Construct() override;
	virtual void Release() override;
};