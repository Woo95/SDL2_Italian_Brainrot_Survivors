#pragma once

#include "SceneUI.h"

class CPressToStartPanel;
class CMainMenuWidget;

enum class EMenuUIState : unsigned char { PressToStart, MainMenu };

class CMenuUI : public CSceneUI
{
public:
	CMenuUI();
	virtual ~CMenuUI();

private:
	CPressToStartPanel* mPressToStart = nullptr;
	CMainMenuWidget* mMainMenu = nullptr;

public:
	virtual bool Init() final;

public:
	void SetMenuState(EMenuUIState state);
};