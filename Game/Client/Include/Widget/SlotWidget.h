#pragma once

#include "UserWidget.h"

// CCharSlotWidget, CItemSlotWidget 공용 슬롯 추상 클래스
class CSlotWidget abstract : public CUserWidget
{
public:
	CSlotWidget() = default;
	virtual ~CSlotWidget() = default;
};