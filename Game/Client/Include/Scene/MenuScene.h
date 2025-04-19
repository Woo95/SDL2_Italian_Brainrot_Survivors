#pragma once

#include "Scene.h"

class CMenuScene : public CScene
{
    friend class CSceneManager;

private:
    CMenuScene();
    ~CMenuScene();

public:
    virtual bool Enter() final;
    virtual bool Exit()  final;

    virtual void LoadResources() final;
};