#include "stdafx.h"
#include "MeoScene.h"
#include "MeoSceneNode.h"
#include "MeoSimpleMesh.h"

MeoScene::MeoScene( ID3D11Device* pDevice )
{
    m_pDevice = pDevice;
}

MeoScene::~MeoScene()
{
}

void MeoScene::Init()
{
    m_pRootNode = std::make_unique<MeoSceneNode>();
}

MeoSceneNode* MeoScene::GetRootNode() const
{
    return m_pRootNode.get();
}

MeoSimpleMesh* MeoScene::CreateSimpleMesh()
{
    return new MeoSimpleMesh( m_pDevice );
}
