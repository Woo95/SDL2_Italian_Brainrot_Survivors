#pragma once

#include "UserWidget.h"

class CSlotWidget;

class CHighlightSelectedSlot : public CUserWidget
{
public:
    CHighlightSelectedSlot();
    virtual ~CHighlightSelectedSlot();

protected:
    virtual void Construct() override;
    virtual void Release() override;

public:
    void SetSlot(CSlotWidget* slot);
};