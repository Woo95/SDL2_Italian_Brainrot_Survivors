#pragma once

#include "SceneUI.h"
#include "../../Core/Utils/SceneUtils.h"
#include "../../Core/Utils/GameDataUtils.h"

class CPlayPanel;
class CPausePanel;
class CLevelUpPanel;
class CGameOverPanel;

class CPlayUI : public CSceneUI
{
public:
	CPlayUI();
	virtual ~CPlayUI();

private:
    CPlayPanel*     mPlay     = nullptr;
    CPausePanel*    mPause    = nullptr;
    CLevelUpPanel*  mLevelUp  = nullptr;
    CGameOverPanel* mGameOver = nullptr;

public:
	virtual bool Init() final;

public:
    void SetUIPanel(EPlaySubState state);

    void SetLevelUpChoice(std::vector<FItem> pool);

    void SetHealthPercent(float percent);
    void SetExpPercent(float percent);
    void SetPlayerLevel(int level);
    void SetKillCounter(int count);
    void SetGameTime(float seconds);

private:
    void BindEventListeners();
};