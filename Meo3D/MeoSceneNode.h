#pragma once

#include <vector>


class MeoSceneNode
{
public:
    MeoSceneNode();
    ~MeoSceneNode();

    MeoSceneNode* GetParentNode() { return m_pParentNode; }

    bool AttachChild( MeoSceneNode* pChildNode );

private:
    MeoSceneNode* m_pParentNode = nullptr;
    std::vector<MeoSceneNode*> m_childNodes;
};

