#pragma once

#include "UserWidget.h"
#include "../Core/Utils/GameDataUtils.h"

class CLevelUpSlot;

class CLevelUpPanel : public CUserWidget
{
public:
	CLevelUpPanel();
	virtual ~CLevelUpPanel();

private:
	std::vector<CLevelUpSlot*> mSlots;

protected:
	virtual void Construct() final;
	virtual void Release() final;

public:
	void SetLevelUpChoicePool(const std::vector<FSelectableItem>& pool);
	const std::vector<CLevelUpSlot*>& GetSlots() const { return mSlots; }

private:
	CLevelUpSlot* CreateLevelUpSlot(int idx, const FVector2D& scale, const FVector2D& pos);
	const FVector2D CalcSlotPos(int col, int row) const;
};