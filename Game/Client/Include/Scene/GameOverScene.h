#pragma once

#include "Scene.h"

class CGameOverScene : public CScene
{
    friend class CSceneManager;

private:
    CGameOverScene();
    virtual ~CGameOverScene();

public:
    virtual bool Enter() final;
    virtual bool Exit()  final;

    virtual void LoadResources() final;
};