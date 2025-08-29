#pragma once

#include "SceneUI.h"
#include "../../Core/Utils/SceneUtils.h"

class CPressToStartPanel;
class CMainMenuPanel;

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
	void SetUIPanel(EMenuSubState state);
};