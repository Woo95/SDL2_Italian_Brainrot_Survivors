#include "PressToStartPanel.h"
#include "AllWidgets.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/SoundManager.h"
#include "../Manager/SceneManager.h"
#include "../Scene/MenuScene.h"

CPressToStartPanel::CPressToStartPanel()
{
    Construct();
}

CPressToStartPanel::~CPressToStartPanel()
{
}

void CPressToStartPanel::Construct()
{
    SetInteractable(true);

    mText = CWidgetUtils::AllocateWidget<CTextBlock>("PressToStartPanel_TextBlock_Text");
    mText->GetTransform()->SetRelativeScale(FVector2D(0.25f, 0.05f));
    mText->GetTransform()->SetRelativePos(0.5f, 0.7f);
    mText->GetTransform()->SetPivot(0.5f, 0.5f);
    mText->SetFont("Font32_CourierPrime_Regular");
    mText->SetText("PRESS TO START");
    AddChild(mText);
}

void CPressToStartPanel::Update(float deltaTime)
{
    CUserWidget::Update(deltaTime);

    mBlinkTimer += deltaTime;

    if (mBlinkTimer >= 0.5f)
    {
        mText->GetEnable() ? mText->Disable() : mText->Enable();

        mBlinkTimer = 0.0f;
    }
}

void CPressToStartPanel::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CPressToStartPanel>(this);
}

void CPressToStartPanel::HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased)
{
    if (isPressed)
    {
		if (CMenuScene* menuScene = static_cast<CMenuScene*>(CSceneManager::GetInst()->GetCurrentScene()))
		{
			CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressIn")->Play();
			menuScene->SetSubState(EMenuSubState::MENU);
		}
    }
}