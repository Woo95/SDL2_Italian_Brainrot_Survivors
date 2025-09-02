#pragma once

#include "UserWidget.h"

class CButton;

class CGameOverPanel : public CUserWidget
{
public:
	CGameOverPanel();
	virtual ~CGameOverPanel();

protected:
	virtual void Construct() final;
	virtual void Release() final;

private:
	CButton* CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize);
};