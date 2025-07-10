#pragma once

#include "SceneUI.h"

class CButton;

class CGameOverUI : public CSceneUI
{
public:
	CGameOverUI();
	virtual ~CGameOverUI();

public:
	virtual bool Init() final;

private:
	CButton* CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize);
};