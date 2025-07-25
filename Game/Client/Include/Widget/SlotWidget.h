#pragma once

#include "UserWidget.h"

// CCharSlotWidget, CPowerUpSlotWidget 공용 슬롯 추상 클래스
// 현재 CHighlightSelectedSlotWidget을 위해 사용중
class CSlotWidget abstract : public CUserWidget
{
public:
	CSlotWidget() = default;
	virtual ~CSlotWidget() = default;
};