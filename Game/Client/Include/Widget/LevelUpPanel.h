#pragma once

#include "UserWidget.h"

class CLevelUpSlot;

class CLevelUpPanel : public CUserWidget
{
public:
	CLevelUpPanel();
	virtual ~CLevelUpPanel();

private:
	CLevelUpSlot* mSlots[3] = {};

protected:
	virtual void Construct() final;
	virtual void Release() final;

private:
	CLevelUpSlot* CreateLevelUpSlot(int idx, const FVector2D& scale, const FVector2D& pos);
	const FVector2D CalcSlotPos(int col, int row) const;
};