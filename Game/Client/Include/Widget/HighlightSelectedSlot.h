#pragma once

#include "UserWidget.h"

class CSlot;

class CHighlightSelectedSlot : public CUserWidget
{
public:
    CHighlightSelectedSlot();
    virtual ~CHighlightSelectedSlot();

protected:
    virtual void Construct() override;
    virtual void Release() override;

public:
    void SetSlot(CSlot* slot);
};