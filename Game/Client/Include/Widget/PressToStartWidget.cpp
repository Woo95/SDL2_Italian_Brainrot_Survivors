#include "PressToStartWidget.h"
#include "TextBlock.h"
#include "../Manager/GameManager.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/SoundManager.h"
#include "../Scene/UI/MenuUI.h"

CPressToStartWidget::CPressToStartWidget()
{
    Construct();
}

CPressToStartWidget::~CPressToStartWidget()
{
}

void CPressToStartWidget::Construct()
{
    SetInteractable(true);

    GetTransform()->SetWorldScale(CGameManager::GetInst()->GetResolution());
    const FVector2D& parentScale = GetTransform()->GetWorldScale();

    mText = CWidgetUtils::AllocateWidget<CTextBlock>("Text_PressToStart");
    mText->GetTransform()->SetWorldScale(parentScale * FVector2D(0.234375f, 0.05f));
    mText->GetTransform()->SetWorldPos((parentScale.x - mText->GetTransform()->GetWorldScale().x) * 0.5f, parentScale.y * 0.7f);
    mText->SetFont("Font32_CourierPrime_Regular");
    mText->SetText("PRESS TO START");
    AddChild(mText);
}

void CPressToStartWidget::Update(float deltaTime)
{
    CUserWidget::Update(deltaTime);

    mBlinkTimer += deltaTime;

    if (mBlinkTimer >= 0.5f)
    {
        mText->GetEnable() ? mText->Disable() : mText->Enable();

        mBlinkTimer = 0.0f;
    }
}

void CPressToStartWidget::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CPressToStartWidget>(this);
}

void CPressToStartWidget::HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased)
{
    if (isPressed)
    {
        CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressIn")->Play();

        ((CMenuUI*)mSceneUI)->SetMenuState(EMenuUIState::MainMenu);
    }
}