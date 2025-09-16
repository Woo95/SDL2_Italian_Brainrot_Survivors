#pragma once

#include "UserWidget.h"

class CTextBlock;

class CResultPanel : public CUserWidget
{
public:
	CResultPanel();
	virtual ~CResultPanel();

private:
	CTextBlock* mSurvivedStat;
	CTextBlock* mGoldEarnedStat;
	CTextBlock* mLevelReachedStat;
	CTextBlock* mEnemiesKilledStat;

protected:
	virtual void Construct() final;
	virtual void Release() final;

public:
	void UpdateSurvivedTime(float time);
	void UpdateGoldEarned(int gold);
	void UpdateLevelReached(int level);
	void UpdateEnemiesKilled(int kill);
};