#pragma once

#include "Scene.h"
#include "../Core/Utils/SceneUtils.h"

class CMenuScene : public CScene
{
    friend class CSceneManager;

private:
    CMenuScene();
    virtual ~CMenuScene();

public:
    virtual bool Enter(void* payload = nullptr) final;
    virtual bool Exit()  final;

    virtual void Update(float deltaTime) final;

    virtual void LoadResources() final;

public:
    void SetSubState(EMenuSubState state);

private:
    void BindEventListeners();
};