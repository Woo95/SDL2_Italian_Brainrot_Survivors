#include "PauseWidget.h"
#include "AllWidgets.h"
#include "../Manager/SceneManager.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/SoundManager.h"

CPauseWidget::CPauseWidget()
{
	Construct();
}

CPauseWidget::~CPauseWidget()
{
}

void CPauseWidget::Construct()
{
    CImage* background = CWidgetUtils::AllocateWidget<CImage>("Image_PauseBG");
    background->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
    background->SetTexture("Texture_UIAtlas");
    background->SetFrame("PauseBG");
    background->SetAlpha(120);
    AddChild(background);

    mBtnQuit = CreateButton("Quit", "RedButton", FVector2D(0.17f, 0.09f), "QUIT", FVector2D(0.5f, 0.6f));
    mBtnQuit->GetTransform()->SetRelativePos(FVector2D(0.39f, 0.9f));
    mBtnQuit->Set9SlicingCorner(FVector2D(10.f, 7.f));
    mBtnQuit->SetCornerRatio(2.0f);
    mBtnQuit->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressOut")->Play();});
    mBtnQuit->AddCallback(EButton::InputEvent::RELEASE, []() {CSceneManager::GetInst()->ChangeRequest(ETransition::CLEAR_THEN_PUSH, ESceneState::MENU);});

    mBtnOption = CreateButton("Option", "BlueButton", FVector2D(0.17f, 0.09f), "OPTIONS", FVector2D(0.65f, 0.6f));
    mBtnOption->GetTransform()->SetRelativePos(FVector2D(0.39f, 0.9f));
    mBtnOption->Set9SlicingCorner(FVector2D(10.f, 7.f));
    mBtnOption->SetCornerRatio(2.0f);
    mBtnOption->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressOut")->Play();});
    mBtnOption->AddCallback(EButton::InputEvent::RELEASE, [this]() {this->ShowPanel(mOptionPanel);});

    mBtnResume = CreateButton("Resume", "BlueButton", FVector2D(0.17f, 0.09f), "RESUME", FVector2D(0.65f, 0.6f));
    mBtnResume->GetTransform()->SetRelativePos(FVector2D(0.61f, 0.9f));
    mBtnResume->Set9SlicingCorner(FVector2D(10.f, 7.f));
    mBtnResume->SetCornerRatio(2.0f);
    mBtnResume->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressOut")->Play();});
    mBtnResume->AddCallback(EButton::InputEvent::RELEASE, [this]() {this->HidePanel();});
    mBtnResume->AddCallback(EButton::InputEvent::RELEASE, []() {CSceneManager::GetInst()->ChangeRequest(ETransition::POP, ESceneState::PAUSE);});

    mOptionPanel = CWidgetUtils::AllocateWidget<COptionPanelWidget>("UserWidget_OptionPanel");
    mOptionPanel->GetTransform()->SetRelativeScale(FVector2D(0.46f, 0.7f));
    mOptionPanel->GetTransform()->SetRelativePos(FVector2D(0.27f, 0.075f));
    AddChild(mOptionPanel);

    HidePanel();
}

void CPauseWidget::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CPauseWidget>(this);
}

void CPauseWidget::ShowPanel(CWidget* panel)
{
    mBtnQuit->Enable();
    mBtnOption->Disable();
    panel->Enable();
}

void CPauseWidget::HidePanel()
{
    mBtnOption->Enable();
    mBtnQuit->Disable();
    mOptionPanel->Disable();
}

CButton* CPauseWidget::CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize)
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