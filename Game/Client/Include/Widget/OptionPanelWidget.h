#pragma once

#include "UserWidget.h"

class COptionPanelWidget : public CUserWidget
{
public:
	COptionPanelWidget();
	virtual ~COptionPanelWidget();

protected:
	virtual void Construct() override;
	virtual void Release() override;
};