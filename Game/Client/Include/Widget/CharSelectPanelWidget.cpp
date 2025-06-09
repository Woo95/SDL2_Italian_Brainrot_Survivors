#include "CharSelectPanelWidget.h"
#include "AllWidgets.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/SoundManager.h"
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

    const FVector2D slotScale = FVector2D(0.1f, 0.1882f);
    const FVector2D offsetX = outerPanel->GetTransform()->GetRelativeScale() * FVector2D(0.0869565f, 0.0f);

    CCharSlotWidget* tralalaSlot = CWidgetUtils::AllocateWidget<CCharSlotWidget, 3>("SelectSlot_TralalaSlot");
    tralalaSlot->GetTransform()->SetRelativeScale(slotScale);
    tralalaSlot->GetTransform()->SetRelativePos(outerPanel->GetTransform()->GetRelativePos() + offsetX + FVector2D(0.0f, 0.15f));
    tralalaSlot->SetName("Tralala");
    tralalaSlot->SetSFX("SFX_Character_Tralala");
    AddChild(tralalaSlot);

    CCharSlotWidget* sahurSlot = CWidgetUtils::AllocateWidget<CCharSlotWidget>("SelectSlot_SahurSlot");
    sahurSlot->GetTransform()->SetRelativeScale(slotScale);
    sahurSlot->GetTransform()->SetRelativePos(tralalaSlot->GetTransform()->GetRelativePos() + offsetX + FVector2D(slotScale.x, 0.0f));
    sahurSlot->SetName("Sahur");
    sahurSlot->SetSFX("SFX_Character_Sahur");
    AddChild(sahurSlot);

    CCharSlotWidget* bananiniSlot = CWidgetUtils::AllocateWidget<CCharSlotWidget>("SelectSlot_BananiniSlot");
    bananiniSlot->GetTransform()->SetRelativeScale(slotScale);
    bananiniSlot->GetTransform()->SetRelativePos(sahurSlot->GetTransform()->GetRelativePos() + offsetX + FVector2D(slotScale.x, 0.0f));
    bananiniSlot->SetName("Bananini");
    bananiniSlot->SetSFX("SFX_Character_Bananini");
    AddChild(bananiniSlot);

    CCharDetailWidget* charDetail = CWidgetUtils::AllocateWidget<CCharDetailWidget, 1>("SelectSlot_BananiniSlot");
    charDetail->GetTransform()->SetRelativeScale(FVector2D(0.44f, 0.1765f));
    charDetail->GetTransform()->SetRelativePos(FVector2D(0.28f, 0.805f));
    AddChild(charDetail);

    //CButton* btnConfirm = CreateButton("Confirm", "GreenButton", FVector2D(0.18f, 0.09f), "Confirm", FVector2D(0.5f, 0.5f));
    //btnConfirm->GetTransform()->SetRelativePos(FVector2D(0.865f, 0.955f));
    //btnConfirm->Set9SlicingCorner(FVector2D(10.f, 7.f));
    //btnConfirm->SetCornerRatio(2.0f);
    //btnConfirm->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressIn")->Play(); });

    CButton* btnStart = CreateButton("Start", "GreenButton", FVector2D(0.18f, 0.09f), "START", FVector2D(0.5f, 0.6f));
    btnStart->GetTransform()->SetRelativePos(FVector2D(0.865f, 0.955f));
    btnStart->Set9SlicingCorner(FVector2D(10.f, 7.f));
    btnStart->SetCornerRatio(2.0f);
    btnStart->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressIn")->Play(); });
    btnStart->AddCallback(EButton::InputEvent::RELEASE, []() {CSceneManager::GetInst()->PendingChange(EScene::State::PLAY);});
}

void CCharSelectPanelWidget::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CCharSelectPanelWidget>(this);
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