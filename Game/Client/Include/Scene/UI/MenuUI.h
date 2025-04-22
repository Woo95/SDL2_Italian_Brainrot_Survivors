#pragma once

#include "SceneUI.h"

class CPressToStartWidget;

enum class EMenuUIState : unsigned char { PressToStart, MainMenu, Options, Start, PowerUp };

class CMenuUI : public CSceneUI
{
public:
	CMenuUI();
	virtual ~CMenuUI();

private:
	EMenuUIState mCurrentState;

	CPressToStartWidget* mPressToStart;

public:
	virtual bool Init() override;

public:
	void SetMenuState(EMenuUIState state);
};