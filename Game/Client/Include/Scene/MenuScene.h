#pragma once

#include "Scene.h"

class CMenuScene : public CScene
{
    friend class CSceneManager;

private:
    CMenuScene();
    virtual ~CMenuScene();

public:
    virtual bool Enter() final;
    virtual bool Exit()  final;

    virtual void LoadResources() final;
};