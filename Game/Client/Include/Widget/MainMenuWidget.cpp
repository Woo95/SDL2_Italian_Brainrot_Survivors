#include "MainMenuWidget.h"
#include "AllWidgets.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/SoundManager.h"
#include "../Manager/SceneManager.h"

CMainMenuWidget::CMainMenuWidget()
{
	Construct();
}

CMainMenuWidget::~CMainMenuWidget()
{
}

void CMainMenuWidget::Construct()
{
    SetInteractable(true);
    GetTransform()->SetWorldScale(1280.f, 800.f);

    const FVector2D& parentScale = GetTransform()->GetWorldScale();

    CImage* menuTopBar = CWidgetUtils::AllocateWidget<CImage>("Image_MenuTopBar");
    menuTopBar->GetTransform()->SetWorldScale(parentScale.x, 77.f);
    menuTopBar->SetTexture("Texture_UIAtlas");
    menuTopBar->SetFrame("MenuTopBar");
    menuTopBar->SetAlpha(180);
    AddChild(menuTopBar);

    CTextBlock* name = CWidgetUtils::AllocateWidget<CTextBlock>("Text_Name");
    name->GetTransform()->SetWorldScale(200.f, 40.f);
    name->GetTransform()->SetWorldPos(parentScale.x * 0.03f, menuTopBar->GetTransform()->GetWorldScale().y * 0.25f);
    name->SetAlignment(ETextBlock::Alignment::CENTER);
    name->SetCharWidth(15.f);
    name->SetFont("Font64_CourierPrime_Regular");
    name->SetText("Chaewan Woo");
    AddChild(name);

    CMoneyHUDWidget* moneyHUD = CWidgetUtils::AllocateWidget<CMoneyHUDWidget, 1>("UserWidget_MoneyHUD");
    moneyHUD->GetTransform()->SetWorldScale(225.f, 64.f);
    moneyHUD->GetTransform()->SetWorldPos((parentScale.x - moneyHUD->GetTransform()->GetWorldScale().x) * 0.5f, menuTopBar->GetTransform()->GetWorldScale().y * 0.1f);
    AddChild(moneyHUD);

    mBtnQuit = CreateButton("Quit", "RedButton", FVector2D(109.f, 60.f), "QUIT", FVector2D(55.f, 20.f));
    mBtnQuit->GetTransform()->SetWorldPos(parentScale.x * 0.5f - 200.f, menuTopBar->GetTransform()->GetWorldScale().y * 0.5f);
    mBtnQuit->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressOut")->Play();});

    mBtnOption = CreateButton("Option", "BlueButton", FVector2D(109.f, 60.f), "OPTIONS", FVector2D(80.f, 20.f));
    mBtnOption->GetTransform()->SetWorldPos(parentScale.x * 0.5f + 200.f, menuTopBar->GetTransform()->GetWorldScale().y * 0.5f );
    mBtnOption->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressOut")->Play();});
    mBtnOption->AddCallback(EButton::InputEvent::RELEASE, [this]() {this->ShowPanel(mOptionPanel);});

    mBtnBack = CreateButton("Back", "RedButton", FVector2D(109.f, 60.f), "BACK", FVector2D(50.f, 20.f));
    mBtnBack->GetTransform()->SetWorldPos(parentScale.x * 0.5f + 200.f, menuTopBar->GetTransform()->GetWorldScale().y * 0.5f);
    mBtnBack->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressOut")->Play();});
    mBtnBack->AddCallback(EButton::InputEvent::RELEASE, [this]() {this->HidePanel();});

    CButton* btnStart = CreateButton("Start", "BlueButton", FVector2D(225.f, 65.f), "START", FVector2D(120.f, 40.f));
    btnStart->GetTransform()->SetWorldPos(parentScale.x * 0.5f, parentScale.y - 277.f);
    btnStart->Set9SlicingCorner(FVector2D(10.f, 7.f));
    btnStart->SetCornerRatio(2.0f);
    btnStart->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressIn")->Play();});
    btnStart->AddCallback(EButton::InputEvent::RELEASE, []() {CSceneManager::GetInst()->PendingChange(EScene::State::PLAY);});

    CButton* btnPowerUp = CreateButton("PowerUp", "GreenButton", FVector2D(182.f, 64.f), "POWER UP", FVector2D(150.f, 35.f));
    btnPowerUp->GetTransform()->SetWorldPos(parentScale.x * 0.5f, parentScale.y - 138.f);
    btnPowerUp->Set9SlicingCorner(FVector2D(10.f, 7.f));
    btnPowerUp->SetCornerRatio(2.0f);
    btnPowerUp->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressIn")->Play();});

    mOptionPanel = CWidgetUtils::AllocateWidget<COptionPanelWidget, 1>("UserWidget_COptionPanel");
    mOptionPanel->GetTransform()->SetWorldScale(parentScale.x * 0.46f, (parentScale.y - menuTopBar->GetTransform()->GetWorldScale().y) * 0.99f);
    mOptionPanel->GetTransform()->SetWorldPos((parentScale.x - mOptionPanel->GetTransform()->GetWorldScale().x) * 0.5f, 
        (menuTopBar->GetTransform()->GetWorldScale().y + parentScale.y - mOptionPanel->GetTransform()->GetWorldScale().y) * 0.5f);
    AddChild(mOptionPanel);

    HidePanel();
}

void CMainMenuWidget::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CMainMenuWidget>(this);
}

void CMainMenuWidget::ShowPanel(CWidget* panel)
{
    mBtnQuit->Disable();
    mBtnOption->Disable();
    mBtnBack->Enable();
    panel->Enable();
}

void CMainMenuWidget::HidePanel()
{
    mBtnQuit->Enable();
    mBtnOption->Enable();
    mBtnBack->Disable();
    mOptionPanel->Disable();
}

CButton* CMainMenuWidget::CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize)
{
    CButton* button = CWidgetUtils::AllocateWidget<CButton>("Button_" + widgetName);
    button->GetTransform()->SetWorldScale(buttonSize);
    button->GetTransform()->SetPivot(0.5f, 0.5f);
    button->SetTexture("Texture_UIAtlas");
    button->SetFrame(buttonFrame);
    AddChild(button);

    CTextBlock* text = CWidgetUtils::AllocateWidget<CTextBlock>("Text_" + widgetName);
    button->AddChild(text);
    text->GetTransform()->SetWorldScale(textSize);
    text->GetTransform()->SetPivot(0.5f, 0.5f);
    text->GetTransform()->SetRelativePos(0.f, 0.f);
    text->SetFont("Font64_CourierPrime_Regular");
    text->SetText(textLabel);

    return button;
}