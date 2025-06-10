#pragma once

#include "UserWidget.h"

class CSlotWidget;

class CSelectHighlightWidget : public CUserWidget
{
public:
    CSelectHighlightWidget();
    virtual ~CSelectHighlightWidget();

protected:
    virtual void Construct() override;
    virtual void Release() override;

public:
    void SetSlot(CSlotWidget* slot);
};