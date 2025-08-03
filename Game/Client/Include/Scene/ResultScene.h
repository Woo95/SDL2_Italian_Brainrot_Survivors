#pragma once

#include "Scene.h"

class CResultScene : public CScene
{
    friend class CSceneManager;

private:
    CResultScene();
    virtual ~CResultScene();

public:
    virtual bool Enter() final;
    virtual bool Exit()  final;

    virtual void LoadResources() final;
};