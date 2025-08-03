#pragma once

#include "SceneUI.h"

class CButton;

class CResultUI : public CSceneUI
{
public:
	CResultUI();
	virtual ~CResultUI();

public:
	virtual bool Init() final;

private:
	CButton* CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize);
};