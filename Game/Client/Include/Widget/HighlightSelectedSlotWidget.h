#pragma once

#include "UserWidget.h"

class CSlotWidget;

class CHighlightSelectedSlotWidget : public CUserWidget
{
public:
    CHighlightSelectedSlotWidget();
    virtual ~CHighlightSelectedSlotWidget();

protected:
    virtual void Construct() override;
    virtual void Release() override;

public:
    void SetSlot(CSlotWidget* slot);
};