#pragma once

#include <memory>

class MeoSceneNode;
class MeoSimpleMesh;


class MeoScene
{
public:
	MeoScene( ID3D11Device* pDevice );
	~MeoScene();
    
    void Init();

    MeoSceneNode* GetRootNode() const;
    MeoSimpleMesh* CreateSimpleMesh();

    const std::vector<std::shared_ptr<MeoSimpleMesh>>& GetSimpleMeshes();

private:
    std::unique_ptr< MeoSceneNode > m_pRootNode = nullptr;
    ID3D11Device* m_pDevice = nullptr;

    std::vector<std::shared_ptr<MeoSimpleMesh>> m_vSimpleMeshes;
};

