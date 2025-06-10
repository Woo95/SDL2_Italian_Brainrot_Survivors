#pragma once

#include "UserWidget.h"

class CCreditsPanelWidget : public CUserWidget
{
public:
	CCreditsPanelWidget();
	virtual ~CCreditsPanelWidget();

protected:
	virtual void Construct() override;
	virtual void Release() override;
};