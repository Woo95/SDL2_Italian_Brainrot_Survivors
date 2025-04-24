#pragma once

#include "SceneUI.h"

class CPressToStartWidget;
class CMainMenuWidget;

enum class EMenuUIState : unsigned char { PressToStart, MainMenu, Options, Start, PowerUp };

class CMenuUI : public CSceneUI
{
public:
	CMenuUI();
	virtual ~CMenuUI();

private:
	EMenuUIState mCurrentState;

	CPressToStartWidget* mPressToStart;
	CMainMenuWidget* mMainMenu;

public:
	virtual bool Init() override;

public:
	void SetMenuState(EMenuUIState state);
};