#pragma once

#include "UserWidget.h"

class CTextBlock;

class CPressToStartPanel : public CUserWidget
{
public:
	CPressToStartPanel();
	virtual ~CPressToStartPanel();

private:
	float mBlinkTimer = 0.0f;

	CTextBlock* mText = nullptr;

protected:
	virtual void Construct() final;
	virtual void Update(float deltaTime) final;
	virtual void Release() final;

	virtual void HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased) override;
};