#pragma once

#include "SceneUI.h"

class CButton;
class CResultPanel;

class CResultUI : public CSceneUI
{
public:
	CResultUI();
	virtual ~CResultUI();

private:
	CResultPanel* mResultPanel = nullptr;

public:
	virtual bool Init() final;

public:
	CResultPanel* GetResultPanel() { return mResultPanel; }

private:
	CButton* CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize);
};