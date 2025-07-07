#include "PlayWidget.h"
#include "AllWidgets.h"
#include "../Manager/SceneManager.h"

CPlayWidget::CPlayWidget()
{
	Construct();
}

CPlayWidget::~CPlayWidget()
{
}

void CPlayWidget::Construct()
{
    CButton* btnPause = CWidgetUtils::AllocateWidget<CButton>("Button_PAUSE");
    btnPause->GetTransform()->SetRelativeScale(FVector2D(0.03f, 0.08f));
    btnPause->GetTransform()->SetRelativePos(FVector2D(0.955f, 0.075f));
    btnPause->SetTexture("Texture_UIAtlas");
    btnPause->SetFrame("PauseButton");
    btnPause->SetAlpha(120);
    btnPause->AddCallback(EButton::InputEvent::RELEASE, []() {CSceneManager::GetInst()->ChangeRequest(ETransition::PUSH, ESceneState::PAUSE);});
    AddChild(btnPause);
}

void CPlayWidget::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CPlayWidget>(this);
}