#include "MainMenuPanel.h"
#include "AllWidgets.h"
#include "../Manager/Data/GameData/GameDataManager.h"
#include "../Manager/Data/GameData/PlayerProfile.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/SoundManager.h"
#include "../Manager/InputManager.h"

CMainMenuPanel::CMainMenuPanel()
{
	Construct();
}

CMainMenuPanel::~CMainMenuPanel()
{
}

void CMainMenuPanel::Construct()
{
    CImage* topBar = CWidgetUtils::AllocateWidget<CImage>("MainMenuPanel_Image_TopBar");
    topBar->GetTransform()->SetRelativeScale(FVector2D(1.0f, 0.1f));
    topBar->SetTexture("Texture_UIAtlas");
    topBar->SetFrame("MenuTopBar");
    topBar->SetAlpha(180);
    AddChild(topBar);

    CTextBlock* name = CWidgetUtils::AllocateWidget<CTextBlock>("MainMenuPanel_TextBlock_Name");
    name->GetTransform()->SetRelativeScale(FVector2D(0.15f, 0.05f));
    name->GetTransform()->SetRelativePos(FVector2D(0.03f, 0.024f));
    name->SetAlignment(ETextBlock::Alignment::CENTER);
    name->SetCharWidth(50.f);
    name->SetFont("Font64_CourierPrime_Regular");
    name->SetText("Chaewan Woo");
    AddChild(name);

    mMoneyHUD = CWidgetUtils::AllocateWidget<CMoneyHUD, 1>("MainMenuPanel_MoneyHUD");
    mMoneyHUD->GetTransform()->SetRelativeScale(FVector2D(0.1758f, 0.08f));
    mMoneyHUD->GetTransform()->SetRelativePos(FVector2D(0.4121f, 0.009625f));
    mMoneyHUD->SetBalance(CGameDataManager::GetInst()->GetPlayerProfile()->GetBalance());
    AddChild(mMoneyHUD);

    mBtnQuit = CreateButton("Quit", "RedButton", FVector2D(0.08515f, 0.075f), "QUIT", FVector2D(0.5f, 0.4f));
    mBtnQuit->GetTransform()->SetRelativePos(FVector2D(0.34375f, 0.048f));
    mBtnQuit->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressOut")->Play();});
    mBtnQuit->AddCallback(EButton::InputEvent::RELEASE, []() {SDL_Event quitEvent; quitEvent.type = SDL_QUIT; SDL_PushEvent(&quitEvent);});

    mBtnOption = CreateButton("Option", "BlueButton", FVector2D(0.08515f, 0.075f), "OPTIONS", FVector2D(0.73f, 0.4f));
    mBtnOption->GetTransform()->SetRelativePos(FVector2D(0.65625f, 0.048f));
    mBtnOption->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressOut")->Play();});
    mBtnOption->AddCallback(EButton::InputEvent::RELEASE, [this]() {this->ShowPanel(mOptionPanel);});

    mBtnBack = CreateButton("Back", "RedButton", FVector2D(0.08515f, 0.075f), "BACK", FVector2D(0.45f, 0.4f));
    mBtnBack->GetTransform()->SetRelativePos(FVector2D(0.65625f, 0.048f));
    mBtnBack->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressOut")->Play();});
    mBtnBack->AddCallback(EButton::InputEvent::RELEASE, [this]() {OnBackButton();});
    mBtnBack->AddCallback(EButton::InputEvent::RELEASE, [this]() {this->HidePanel();});

    mBtnStart = CreateButton("Start", "BlueButton", FVector2D(0.1758f, 0.08125f), "START", FVector2D(0.53f, 0.63f));
    mBtnStart->GetTransform()->SetRelativePos(FVector2D(0.5f, 0.653125f));
    mBtnStart->Set9SlicingCorner(FVector2D(10.0f, 7.0f));
    mBtnStart->SetCornerRatio(2.0f);
    mBtnStart->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressIn")->Play();});
    mBtnStart->AddCallback(EButton::InputEvent::RELEASE, [this]() {this->ShowPanel(mCharSelectPanel);});

    mBtnPowerUp = CreateButton("PowerUp", "GreenButton", FVector2D(0.1422f, 0.08f), "POWER UP", FVector2D(0.80f, 0.50f));
    mBtnPowerUp->GetTransform()->SetRelativePos(FVector2D(0.5f, 0.8275f));
    mBtnPowerUp->Set9SlicingCorner(FVector2D(10.0f, 7.0f));
    mBtnPowerUp->SetCornerRatio(2.0f);
    mBtnPowerUp->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressIn")->Play();});
    mBtnPowerUp->AddCallback(EButton::InputEvent::RELEASE, [this]() {this->ShowPanel(mPowerUpSelectPanel);});

    mBtnCredits = CreateButton("Credits", "BlueCircularButton", FVector2D(0.12f, 0.035f), "credits", FVector2D(0.6f, 0.8f));
    mBtnCredits->FindWidget(std::hash<std::string>()("MainMenuPanel_TextBlock_Credits"))->GetTransform()->SetRelativePos(0.0f, 0.1f);
    mBtnCredits->GetTransform()->SetRelativePos(FVector2D(0.5f, 0.945f));
    mBtnCredits->Set9SlicingCorner(FVector2D(7.0f, 7.0f));
    mBtnCredits->SetCornerRatio(2.0f);
    mBtnCredits->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressIn")->Play();});
    mBtnCredits->AddCallback(EButton::InputEvent::RELEASE, [this]() {this->ShowPanel(mCreditsPanel);});

    mOptionPanel = CWidgetUtils::AllocateWidget<COptionPanel, 1>("MainMenuPanel_OptionPanel");
    mOptionPanel->GetTransform()->SetRelativeScale(FVector2D(0.46f, 0.7f));
    mOptionPanel->GetTransform()->SetRelativePos(FVector2D(0.27f, 0.12f));
    AddChild(mOptionPanel);

    mCharSelectPanel = CWidgetUtils::AllocateWidget<CCharacterSelectPanel, 1>("MainMenuPanel_CharSelectPanel");
    mCharSelectPanel->GetTransform()->SetRelativeScale(FVector2D(1.0f, 0.85f));
    mCharSelectPanel->GetTransform()->SetRelativePos(FVector2D(0.0f, 0.12f));
    AddChild(mCharSelectPanel);

    mPowerUpSelectPanel = CWidgetUtils::AllocateWidget<CPowerUpSelectPanel, 1>("MainMenuPanel_PowerUpSelectPanel");
    mPowerUpSelectPanel->GetTransform()->SetRelativeScale(FVector2D(0.46f, 0.85f));
    mPowerUpSelectPanel->GetTransform()->SetRelativePos(FVector2D(0.27f, 0.12f));
    AddChild(mPowerUpSelectPanel);

    mCreditsPanel = CWidgetUtils::AllocateWidget<CCreditsPanel, 1>("MainMenuPanel_CreditsPanel");
    mCreditsPanel->GetTransform()->SetRelativeScale(FVector2D(0.46f, 0.85f));
    mCreditsPanel->GetTransform()->SetRelativePos(FVector2D(0.27f, 0.12f));
    AddChild(mCreditsPanel);

    HidePanel();
}

void CMainMenuPanel::Update(float deltaTime)
{
    CUserWidget::Update(deltaTime);

    if (CInputManager::GetInst()->GetKeyState(SDL_SCANCODE_ESCAPE, EKeyAction::PRESS))
    {
        if (mOptionPanel->GetEnable() || mCharSelectPanel->GetEnable() || mPowerUpSelectPanel->GetEnable() || mCreditsPanel->GetEnable())
        {
            CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressOut")->Play();
            mCharSelectPanel->OnBackButton();
            mPowerUpSelectPanel->OnBackButton();
            HidePanel();
        }
    }
}

void CMainMenuPanel::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CMainMenuPanel>(this);
}

void CMainMenuPanel::ShowPanel(CWidget* panel)
{
    mBtnQuit->Disable();
    mBtnStart->Disable();
    mBtnOption->Disable();
    mBtnPowerUp->Disable();
    mBtnCredits->Disable();
    mBtnBack->Enable();
    panel->Enable();
}

void CMainMenuPanel::HidePanel()
{
    mBtnQuit->Enable();
    mBtnStart->Enable();
    mBtnOption->Enable();
    mBtnPowerUp->Enable();
    mBtnCredits->Enable();
    mBtnBack->Disable();
    mOptionPanel->Disable();
    mCharSelectPanel->Disable();
    mPowerUpSelectPanel->Disable();
    mCreditsPanel->Disable();
}

void CMainMenuPanel::OnBackButton()
{
    if (mCharSelectPanel->GetEnable())
        mCharSelectPanel->OnBackButton();
    else if (mPowerUpSelectPanel->GetEnable())
        mPowerUpSelectPanel->OnBackButton();
}

CButton* CMainMenuPanel::CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize)
{
    CButton* button = CWidgetUtils::AllocateWidget<CButton>("MainMenuPanel_Button_" + widgetName);
    button->GetTransform()->SetRelativeScale(buttonSize);
    button->GetTransform()->SetPivot(0.5f, 0.5f);
    button->SetTexture("Texture_UIAtlas");
    button->SetFrame(buttonFrame);
    AddChild(button);

    CTextBlock* text = CWidgetUtils::AllocateWidget<CTextBlock>("MainMenuPanel_TextBlock_" + widgetName);
    button->AddChild(text);
    text->GetTransform()->SetRelativeScale(textSize);
    text->GetTransform()->SetPivot(0.5f, 0.5f);
    text->GetTransform()->SetRelativePos(0.0f, 0.0f);
    text->SetFont("Font64_CourierPrime_Regular");
    text->SetText(textLabel);

    return button;
}