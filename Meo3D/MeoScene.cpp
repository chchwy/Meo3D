#include "stdafx.h"
#include "MeoScene.h"
#include "MeoSceneNode.h"


MeoScene::MeoScene()
{
}

MeoScene::~MeoScene()
{
}

void MeoScene::Init()
{
    m_pRootNode = std::make_unique<MeoSceneNode>();
}

MeoSceneNode* MeoScene::GetRootNode()
{
    return m_pRootNode.get();
}
