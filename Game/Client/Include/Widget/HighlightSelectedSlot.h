#pragma once

#include "UserWidget.h"

class CSlot;

class CHighlightSelectedSlot : public CUserWidget
{
public:
    CHighlightSelectedSlot();
    virtual ~CHighlightSelectedSlot();

protected:
    virtual void Construct() final;
    virtual void Release() final;

public:
    void SetSlot(CSlot* slot);
};