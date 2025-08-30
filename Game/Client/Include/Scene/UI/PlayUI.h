#pragma once

#include "SceneUI.h"
#include "../../Core/Utils/SceneUtils.h"

class CPlayPanel;
class CPausePanel;
class CLevelUpPanel;

class CPlayUI : public CSceneUI
{
public:
	CPlayUI();
	virtual ~CPlayUI();

private:
    CPlayPanel*    mPlay    = nullptr;
    CPausePanel*   mPause   = nullptr;
    CLevelUpPanel* mLevelUp = nullptr;

public:
	virtual bool Init() final;

public:
    void SetUIPanel(EPlaySubState state);

    void SetHealthPercent(float percent);
    void SetExpPercent(float percent);
    void SetPlayerLevel(int level);
    void SetKillCounter(int count);
    void SetGameTime(float seconds);
};