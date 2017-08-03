#pragma once

class MeoSceneNode;


class MeoScene
{
public:
	MeoScene();
	~MeoScene();
    


private:
    MeoSceneNode* m_pRootNode = nullptr;
};

