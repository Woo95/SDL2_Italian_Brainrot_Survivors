#pragma once

#include "UserWidget.h"

// 모든 슬롯의 부모이자 추상 클래스
// 현재 CHighlightSelectedSlot을 위해 사용
class CSlot abstract : public CUserWidget
{
public:
	CSlot() = default;
	virtual ~CSlot() = default;
};