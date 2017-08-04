#pragma once

#include <memory>

class MeoSceneNode;


class MeoScene
{
public:
	MeoScene();
	~MeoScene();
    
    void Init();

    MeoSceneNode* GetRootNode();

private:
    std::unique_ptr< MeoSceneNode > m_pRootNode = nullptr;
};

