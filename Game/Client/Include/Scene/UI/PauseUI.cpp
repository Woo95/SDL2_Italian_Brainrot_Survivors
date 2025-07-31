#include "PauseUI.h"
#include "../../Widget/AllWidgets.h"
#include "../../Manager/GameManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/Data/Resource/AssetManager.h"
#include "../../Manager/Data/Resource/SoundManager.h"

CPauseUI::CPauseUI()
{
}

CPauseUI::~CPauseUI()
{
}

bool CPauseUI::Init()
{
    const FVector2D& resolution = CGameManager::GetInst()->GetResolution();

    CImage* background = CWidgetUtils::AllocateWidget<CImage>("PauseUI_Image_PauseBG");
    background->GetTransform()->SetWorldScale(resolution * FVector2D(1.0f, 1.0f));
    background->SetTexture("Texture_UIAtlas");
    background->SetFrame("PauseBG");
    background->SetAlpha(120);
    AddWidget(background);

    mBtnQuit = CreateButton("Quit", "RedButton", resolution * FVector2D(0.17f, 0.09f), "QUIT", FVector2D(0.5f, 0.6f));
    mBtnQuit->GetTransform()->SetWorldPos(resolution * FVector2D(0.39f, 0.9f));
    mBtnQuit->Set9SlicingCorner(FVector2D(10.f, 7.f));
    mBtnQuit->SetCornerRatio(2.0f);
    mBtnQuit->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressOut")->Play();});
    mBtnQuit->AddCallback(EButton::InputEvent::RELEASE, []() {CSceneManager::GetInst()->ChangeRequest(ETransition::CLEAR_THEN_PUSH, ESceneState::GAMEOVER);});

    mBtnOption = CreateButton("Option", "BlueButton", resolution * FVector2D(0.17f, 0.09f), "OPTIONS", FVector2D(0.65f, 0.6f));
    mBtnOption->GetTransform()->SetWorldPos(resolution * FVector2D(0.39f, 0.9f));
    mBtnOption->Set9SlicingCorner(FVector2D(10.f, 7.f));
    mBtnOption->SetCornerRatio(2.0f);
    mBtnOption->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressOut")->Play();});
    mBtnOption->AddCallback(EButton::InputEvent::RELEASE, [this]() {this->ShowPanel(mOptionPanel);});

    mBtnResume = CreateButton("Resume", "BlueButton", resolution * FVector2D(0.17f, 0.09f), "RESUME", FVector2D(0.65f, 0.6f));
    mBtnResume->GetTransform()->SetWorldPos(resolution * FVector2D(0.61f, 0.9f));
    mBtnResume->Set9SlicingCorner(FVector2D(10.f, 7.f));
    mBtnResume->SetCornerRatio(2.0f);
    mBtnResume->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressOut")->Play();});
    mBtnResume->AddCallback(EButton::InputEvent::RELEASE, [this]() {this->HidePanel();});
    mBtnResume->AddCallback(EButton::InputEvent::RELEASE, []() {CSceneManager::GetInst()->ChangeRequest(ETransition::POP, ESceneState::PAUSE);});

    mOptionPanel = CWidgetUtils::AllocateWidget<COptionPanel>("UserWidget_OptionPanel");
    mOptionPanel->GetTransform()->SetWorldScale(resolution * FVector2D(0.46f, 0.7f));
    mOptionPanel->GetTransform()->SetWorldPos(resolution * FVector2D(0.27f, 0.075f));
    AddWidget(mOptionPanel);

    HidePanel();

    return true;
}

void CPauseUI::ShowPanel(CWidget* panel)
{
    mBtnQuit->Enable();
    mBtnOption->Disable();
    panel->Enable();
}

void CPauseUI::HidePanel()
{
    mBtnOption->Enable();
    mBtnQuit->Disable();
    mOptionPanel->Disable();
}

CButton* CPauseUI::CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize)
{
    CButton* button = CWidgetUtils::AllocateWidget<CButton>("PauseUI_Button_" + widgetName);
    button->GetTransform()->SetWorldScale(buttonSize);
    button->GetTransform()->SetPivot(0.5f, 0.5f);
    button->SetTexture("Texture_UIAtlas");
    button->SetFrame(buttonFrame);
    AddWidget(button);

    CTextBlock* text = CWidgetUtils::AllocateWidget<CTextBlock>("PauseUI_TextBlock_" + widgetName);
    button->AddChild(text);
    text->GetTransform()->SetRelativeScale(textSize);
    text->GetTransform()->SetPivot(0.5f, 0.5f);
    text->GetTransform()->SetRelativePos(0.0f, 0.0f);
    text->SetFont("Font64_CourierPrime_Regular");
    text->SetText(textLabel);

    return button;
}