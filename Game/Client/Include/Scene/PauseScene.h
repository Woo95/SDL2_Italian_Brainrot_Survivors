#pragma once

#include "Scene.h"

class CPauseScene : public CScene
{
    friend class CSceneManager;

private:
    CPauseScene();
    virtual ~CPauseScene();

public:
    virtual bool Enter() final;
    virtual bool Exit()  final;

    virtual void Update(float deltaTime) final;

    virtual void LoadResources() final;
};