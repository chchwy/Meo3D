#include "stdafx.h"
#include "MeoScene.h"
#include "MeoSceneNode.h"
#include "MeoSimpleMesh.h"

MeoScene::MeoScene(ID3D11Device* pDevice)
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
    std::shared_ptr<MeoSimpleMesh> spMesh = std::make_shared<MeoSimpleMesh>(m_pDevice);
    spMesh->SetScene(this);
    m_vSimpleMeshes.push_back(spMesh);

    return spMesh.get();
}

const std::vector<std::shared_ptr<MeoSimpleMesh>>&
MeoScene::GetSimpleMeshes()
{
    return m_vSimpleMeshes;
}
