#pragma once

#include "SceneUI.h"

class CPressToStartPanel;
class CMainMenuPanel;

enum class EMenuUIState : unsigned char { PressToStart, MainMenu };

class CMenuUI : public CSceneUI
{
public:
	CMenuUI();
	virtual ~CMenuUI();

private:
	CPressToStartPanel* mPressToStart = nullptr;
	CMainMenuPanel* mMainMenu = nullptr;

public:
	virtual bool Init() final;

public:
	void SetMenuState(EMenuUIState state);
};