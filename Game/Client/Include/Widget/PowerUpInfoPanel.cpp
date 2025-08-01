#include "PowerUpInfoPanel.h"
#include "AllWidgets.h"
#include "../Manager/Data/GameData/GameDataManager.h"
#include "../Manager/Data/GameData/PowerUpDataManager.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/SoundManager.h"

CPowerUpInfoPanel::CPowerUpInfoPanel()
{
	Construct();
}

CPowerUpInfoPanel::~CPowerUpInfoPanel()
{
}

void CPowerUpInfoPanel::Construct()
{
    CImage* panel = CWidgetUtils::AllocateWidget<CImage>("PowerUpInfoPanel_Image_Panel");
    panel->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
    panel->SetTexture("Texture_UIAtlas");
    panel->SetFrame("SelectSlotBox");
    panel->Set9SlicingCorner(FVector2D(6.0f, 6.0f));
    panel->SetCornerRatio(1.5f);
    AddChild(panel);

    mName = CWidgetUtils::AllocateWidget<CTextBlock>("PowerUpInfoPanel_TextBlock_Name");
    mName->GetTransform()->SetRelativeScale(FVector2D(0.2f, 0.19f));
    mName->GetTransform()->SetRelativePos(FVector2D(0.2f, 0.55f));
    mName->SetAlignment(ETextBlock::Alignment::LEFT);
    mName->SetCharWidth(12.5f);
    mName->SetFont("Font64_CourierPrime_Regular");
    mName->SetText(" ");
    AddChild(mName);

    CImage* powerUpBox = CWidgetUtils::AllocateWidget<CImage>("PowerUpInfoPanel_Image_PowerUpBox");
    powerUpBox->GetTransform()->SetRelativeScale(FVector2D(0.09f, 0.425f));
    powerUpBox->GetTransform()->SetRelativePos(FVector2D(0.3f, 3.85f));
    powerUpBox->GetTransform()->SetPivot(0.5f, 0.5f);
    powerUpBox->SetTexture("Texture_UIAtlas");
    powerUpBox->SetFrame("PowerUpBox");
    AddChild(powerUpBox);

    mPowerUpIcon = CWidgetUtils::AllocateWidget<CImage>("PowerUpInfoPanel_Image_PowerUpIcon");
    mPowerUpIcon->GetTransform()->SetRelativeScale(FVector2D(0.7f, 0.7f));
    mPowerUpIcon->GetTransform()->SetPivot(0.5f, 0.5f);
    mPowerUpIcon->SetTexture("Texture_ItemAtlas");
    mPowerUpIcon->SetFrame("Empty");
    powerUpBox->AddChild(mPowerUpIcon);

    mDescription1 = CWidgetUtils::AllocateWidget<CTextBlock>("PowerUpInfoPanel_TextBlock_Desc1");
    mDescription1->GetTransform()->SetRelativeScale(0.55f, 0.19f);
    mDescription1->GetTransform()->SetRelativePos(0.5f, 2.5f);
    mDescription1->SetAlignment(ETextBlock::Alignment::LEFT);
    mDescription1->SetCharWidth(12.5f);
    mDescription1->SetFont("Font64_CourierPrime_Regular");
    mDescription1->SetText(" ");
    AddChild(mDescription1);

    mDescription2 = CWidgetUtils::AllocateWidget<CTextBlock>("PowerUpInfoPanel_TextBlock_Desc2");
    mDescription2->GetTransform()->SetRelativeScale(0.55f, 0.19f);
    mDescription2->GetTransform()->SetRelativePos(0.5f, 4.0f);
    mDescription2->SetAlignment(ETextBlock::Alignment::LEFT);
    mDescription2->SetCharWidth(12.5f);
    mDescription2->SetFont("Font64_CourierPrime_Regular");
    mDescription2->SetText(" ");
    AddChild(mDescription2);

    mMoneyIcon = CWidgetUtils::AllocateWidget<CImage>("PowerUpInfoPanel_Image_MoneyIcon");
    mMoneyIcon->GetTransform()->SetRelativeScale(FVector2D(0.039f, 0.2f));
    mMoneyIcon->GetTransform()->SetRelativePos(FVector2D(1.85f, 1.05f));
    mMoneyIcon->SetTexture("Texture_UIAtlas");
    mMoneyIcon->SetFrame("CoinIcon");
    AddChild(mMoneyIcon);

    mPrice = CWidgetUtils::AllocateWidget<CTextBlock>("PowerUpInfoPanel_TextBlock_Price");
    mPrice->GetTransform()->SetRelativeScale(FVector2D(0.1f, 0.19f));
    mPrice->GetTransform()->SetRelativePos(FVector2D(1.95f, 1.1f));
    mPrice->SetAlignment(ETextBlock::Alignment::LEFT);
    mPrice->SetCharWidth(13.0f);
    mPrice->SetFont("Font64_CourierPrime_Regular");
    mPrice->SetText("0");
    AddChild(mPrice);

    mBtnBuy = CreateButton("Buy", "GreenButton", FVector2D(0.2f, 0.5f), "Buy", FVector2D(0.4f, 0.4f));
    mBtnBuy->GetTransform()->SetRelativePos(FVector2D(2.01f, 4.15f));
    mBtnBuy->Set9SlicingCorner(FVector2D(10.0f, 7.0f));
    mBtnBuy->SetCornerRatio(2.0f);
    mBtnBuy->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressIn")->Play();});
    mBtnBuy->AddCallback(EButton::InputEvent::RELEASE, [this]() {((CPowerUpSelectPanel*)this->mParent)->OnBuyButton();});
}

void CPowerUpInfoPanel::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CPowerUpInfoPanel>(this);
}

void CPowerUpInfoPanel::ShowInfo(CPowerUpSlot* slot)
{
    const FPowerUpData& powerUpData = CGameDataManager::GetInst()->GetPowerUpDataManager()->GetPowerUpData(slot->GetType());

    mName->SetText(slot->GetNameTextBlock()->GetText());
    mDescription1->SetText(powerUpData.description1);
    mDescription2->SetText(powerUpData.description2);
    mPrice->SetText(std::to_string(powerUpData.price));
    mPowerUpIcon->SetFrame(powerUpData.name);

    slot->IsPurchased() ? OnPurchase(true) : OnPurchase(false);
}

void CPowerUpInfoPanel::OnPurchase(bool purchased)
{
    if (purchased)
    {
        mMoneyIcon->Disable();
        mPrice->Disable();
        mBtnBuy->Disable();
    }
    else
    {
        mMoneyIcon->Enable();
        mPrice->Enable();
        mBtnBuy->Enable();
    }
}

CButton* CPowerUpInfoPanel::CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize)
{
    CButton* button = CWidgetUtils::AllocateWidget<CButton>("PowerUpInfoPanel_Button_" + widgetName);
    button->GetTransform()->SetRelativeScale(buttonSize);
    button->GetTransform()->SetPivot(0.5f, 0.5f);
    button->SetTexture("Texture_UIAtlas");
    button->SetFrame(buttonFrame);
    AddChild(button);

    CTextBlock* text = CWidgetUtils::AllocateWidget<CTextBlock>("PowerUpInfoPanel_TextBlock_" + widgetName);
    button->AddChild(text);
    text->GetTransform()->SetRelativeScale(textSize);
    text->GetTransform()->SetPivot(0.5f, 0.5f);
    text->GetTransform()->SetRelativePos(0.0f, 0.0f);
    text->SetFont("Font64_CourierPrime_Regular");
    text->SetText(textLabel);

    return button;
}
