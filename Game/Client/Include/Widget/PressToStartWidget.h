#pragma once

#include "UserWidget.h"

class CTextBlock;

class CPressToStartWidget : public CUserWidget
{
public:
	CPressToStartWidget();
	virtual ~CPressToStartWidget();

private:
	float mBlinkTimer = 0.0f;

	CTextBlock* mText = nullptr;

protected:
	virtual void Construct() override;
	virtual void Update(float deltaTime) override;
	virtual void Release() override;

	virtual void HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased) override;
};