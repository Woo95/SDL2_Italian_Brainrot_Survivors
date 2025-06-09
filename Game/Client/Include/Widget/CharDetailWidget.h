#pragma once

#include "UserWidget.h"

class CTextBlock;

class CCharDetailWidget : public CUserWidget
{
public:
    CCharDetailWidget();
    virtual ~CCharDetailWidget();

protected:
    virtual void Construct() override;
    virtual void Release() override;

private:
    CTextBlock* mName;
};