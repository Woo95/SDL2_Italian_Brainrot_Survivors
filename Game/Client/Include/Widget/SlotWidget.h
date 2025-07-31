#pragma once

#include "UserWidget.h"

// 모든 슬롯의 부모이자 추상 클래스
// 현재 CHighlightSelectedSlotWidget을 위해 사용
class CSlotWidget abstract : public CUserWidget
{
public:
	CSlotWidget() = default;
	virtual ~CSlotWidget() = default;
};