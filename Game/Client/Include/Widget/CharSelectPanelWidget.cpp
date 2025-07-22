#include "CharSelectPanelWidget.h"
#include "AllWidgets.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/SoundManager.h"
#include "../Manager/Data/GameData/GameDataManager.h"
#include "../Manager/Data/GameData/PlayerData.h"
#include "../Manager/SceneManager.h"

CCharSelectPanelWidget::CCharSelectPanelWidget()
{
    Construct();
}

CCharSelectPanelWidget::~CCharSelectPanelWidget()
{
}

void CCharSelectPanelWidget::Construct()
{
    SetInteractable(true);

    CImage* outerPanel = CWidgetUtils::AllocateWidget<CImage>("Image_CharSelectPanelBox");
    outerPanel->GetTransform()->SetRelativeScale(FVector2D(0.46f, 1.0f));
    outerPanel->GetTransform()->SetRelativePos(FVector2D(0.27f, 0.0f));
    outerPanel->SetTexture("Texture_UIAtlas");
    outerPanel->SetFrame("PanelBox");
    outerPanel->Set9SlicingCorner(FVector2D(15.f, 15.f));
    outerPanel->SetCornerRatio(1.25f);
    AddChild(outerPanel);

    CTextBlock* category = CWidgetUtils::AllocateWidget<CTextBlock>("Text_CharSelectCategory");
    category->GetTransform()->SetRelativeScale(outerPanel->GetTransform()->GetRelativeScale() * FVector2D(0.8f, 0.065f));
    category->GetTransform()->SetRelativePos(outerPanel->GetTransform()->GetRelativePos() + outerPanel->GetTransform()->GetRelativeScale() * FVector2D(0.1f, 0.0325f));
    category->SetAlignment(ETextBlock::Alignment::CENTER);
    category->SetCharWidth(50.f);
    category->SetFont("Font64_CourierPrime_Regular");
    category->SetText("Character Selection");
    AddChild(category);

    ///// Slot-Related Code - BEGIN /////
    const FVector2D slotScale = FVector2D(0.1f, 0.188f);
    const FVector2D slotStartPos = outerPanel->GetTransform()->GetRelativeScale() * FVector2D(0.675f, 0.17f);
    float offsetX = slotScale.x * 1.37f;

    CCharSlotWidget* tralalaSlot = CreateCharSlotWidget("Tralala", slotScale, slotStartPos);
    tralalaSlot->SetCharacterType(ECharacterType::TRALALA);
    tralalaSlot->GetAnimatedImage()->GetTransform()->SetRelativeScale(FVector2D(62.0f, 45.0f) * 0.01f);
    tralalaSlot->GetAnimatedImage()->GetTransform()->SetRelativePos(FVector2D(0.5f, 3.0f));

    CCharSlotWidget* sahurSlot = CreateCharSlotWidget("Sahur", slotScale, tralalaSlot->GetTransform()->GetRelativePos() + FVector2D(offsetX, 0.0f));
    sahurSlot->SetCharacterType(ECharacterType::SAHUR);
    sahurSlot->GetAnimatedImage()->GetTransform()->SetRelativeScale(FVector2D(38.0f, 45.0f) * 0.012f);
    sahurSlot->GetAnimatedImage()->GetTransform()->SetRelativePos(FVector2D(0.63f, 2.4f));

    CCharSlotWidget* bananiniSlot = CreateCharSlotWidget("Bananini", slotScale, sahurSlot->GetTransform()->GetRelativePos() + FVector2D(offsetX, 0.0f));
    bananiniSlot->SetCharacterType(ECharacterType::BANANINI);
    bananiniSlot->GetAnimatedImage()->GetTransform()->SetRelativeScale(FVector2D(59.0f, 50.0f) * 0.01f);
    bananiniSlot->GetAnimatedImage()->GetTransform()->SetRelativePos(FVector2D(0.63f, 2.7f));

    mHighlight = CWidgetUtils::AllocateWidget<CHighlightSelectedSlotWidget, 2>("HighlighSelectedSlot_Character");
    mHighlight->GetTransform()->SetRelativeScale(slotScale * 1.1f);
    mHighlight->Disable();
    AddChild(mHighlight);

    mDetail = CWidgetUtils::AllocateWidget<CCharInfoWidget, 1>("CharacterInfo_Details");
    mDetail->GetTransform()->SetRelativeScale(FVector2D(0.44f, 0.1765f));
    mDetail->GetTransform()->SetRelativePos(FVector2D(0.28f, 0.805f));
    mDetail->Disable();
    AddChild(mDetail);
    ///// Slot-Related Code - END /////

    mBtnConfirm = CreateButton("Confirm", "GreenButton", FVector2D(0.18f, 0.09f), "Confirm", FVector2D(0.5f, 0.5f));
    mBtnConfirm->GetTransform()->SetRelativePos(FVector2D(0.865f, 0.955f));
    mBtnConfirm->Set9SlicingCorner(FVector2D(10.f, 7.f));
    mBtnConfirm->SetCornerRatio(2.0f);
    mBtnConfirm->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressIn")->Play();});
    mBtnConfirm->AddCallback(EButton::InputEvent::RELEASE, [this]() {mBtnStart->Enable();});
    mBtnConfirm->Disable();

    mBtnStart = CreateButton("Start", "GreenButton", FVector2D(0.18f, 0.09f), "START", FVector2D(0.5f, 0.6f));
    mBtnStart->GetTransform()->SetRelativePos(FVector2D(0.865f, 0.955f));
    mBtnStart->Set9SlicingCorner(FVector2D(10.f, 7.f));
    mBtnStart->SetCornerRatio(2.0f);
    mBtnStart->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressIn")->Play();});
    mBtnStart->AddCallback(EButton::InputEvent::RELEASE, []() {CSceneManager::GetInst()->ChangeRequest(ETransition::SWAP, ESceneState::PLAY);});
    mBtnStart->Disable();
}

void CCharSelectPanelWidget::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CCharSelectPanelWidget>(this);
}

void CCharSelectPanelWidget::OnBackButton()
{
    mHighlight->Disable();
    mDetail->Disable();
    mBtnConfirm->Disable();
    mBtnStart->Disable();

    if (mPrevSlot)
    {
        mPrevSlot->StopSFX();
        mPrevSlot->GetAnimatedImage()->SetAnimating(false);
        mPrevSlot->GetAnimatedImage()->ResetAnimation();
    }
}

void CCharSelectPanelWidget::OnSlotClicked(CCharSlotWidget* slot)
{
    // Data
    CGameDataManager::GetInst()->GetPlayerData()->SetSelectedCharacter(slot->GetCharType());

    // UI 
    mHighlight->Enable();
    mHighlight->SetSlot(slot);
    slot->GetAnimatedImage()->SetAnimating(true);
    mDetail->Enable();
    mDetail->ShowDetail(slot);
    mBtnConfirm->Enable();
    mBtnStart->Disable();

    // Sound
    slot->PlaySFX();

    // Previous Slot
    if (mPrevSlot && mPrevSlot != slot)
    {
        mPrevSlot->StopSFX();
        mPrevSlot->GetAnimatedImage()->SetAnimating(false);
        mPrevSlot->GetAnimatedImage()->ResetAnimation();
    }

    mPrevSlot = slot;
}

CButton* CCharSelectPanelWidget::CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize)
{
    CButton* button = CWidgetUtils::AllocateWidget<CButton>("Button_" + widgetName);
    button->GetTransform()->SetRelativeScale(buttonSize);
    button->GetTransform()->SetPivot(0.5f, 0.5f);
    button->SetTexture("Texture_UIAtlas");
    button->SetFrame(buttonFrame);
    AddChild(button);

    CTextBlock* text = CWidgetUtils::AllocateWidget<CTextBlock>("Text_" + widgetName);
    button->AddChild(text);
    text->GetTransform()->SetRelativeScale(textSize);
    text->GetTransform()->SetPivot(0.5f, 0.5f);
    text->GetTransform()->SetRelativePos(0.0f, 0.0f);
    text->SetFont("Font64_CourierPrime_Regular");
    text->SetText(textLabel);

    return button;
}

CCharSlotWidget* CCharSelectPanelWidget::CreateCharSlotWidget(const std::string& widgetName, const FVector2D& scale, const FVector2D& pos)
{
    CCharSlotWidget* slot = CWidgetUtils::AllocateWidget<CCharSlotWidget, 3>("CharacterSlot_" + widgetName);
    slot->GetTransform()->SetRelativeScale(scale);
    slot->GetTransform()->SetRelativePos(pos);
    slot->GetTextBlock()->SetText(widgetName);
    slot->SetSFX("SFX_Character_" + widgetName);
    slot->GetAnimatedImage()->SetTexture("Texture_" + widgetName);
    slot->GetAnimatedImage()->SetFrame(widgetName);
    slot->SetOnClick([this](CCharSlotWidget* slot) {this->OnSlotClicked(slot);});
    AddChild(slot);

    return slot;
};