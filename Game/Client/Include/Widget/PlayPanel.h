#pragma once

#include "UserWidget.h"
#include "../Core/Utils/GameDataUtils.h"

class CProgressBar;
class CExpBar;
class CKillCounter;
class CCoinCounter;
class CTimeHUD;
class CInventoryPanel;

class CPlayPanel : public CUserWidget
{
public:
	CPlayPanel();
	virtual ~CPlayPanel();

private:
	CProgressBar*    mHealthBar   = nullptr;
	CExpBar*         mExpBar      = nullptr;
	CKillCounter*    mKillCounter = nullptr;
	CCoinCounter*    mCoinCounter = nullptr;
	CTimeHUD*        mTimeHUD     = nullptr;
	CInventoryPanel* mInventory   = nullptr;

protected:
	virtual void Construct() final;
	virtual void Release() final;

public:
	void SetHealthPercent(float percent);
	void SetExpPercent(float percent);
	void SetPlayerLevel(int level);
	void SetKillCounter(int count);
	void SetCoinCounter(int count);
	void SetGameTime(float seconds);
	void SetInventorySlot(EWeaponType type);
	void SetInventorySlot(EPowerUpType type);
};