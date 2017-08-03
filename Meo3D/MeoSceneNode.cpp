#include "stdafx.h"
#include "MeoSceneNode.h"


MeoSceneNode::MeoSceneNode()
{
}


MeoSceneNode::~MeoSceneNode()
{
}

bool MeoSceneNode::AttachChild( MeoSceneNode* pChildNode )
{
    auto it = std::find( m_childNodes.begin(), m_childNodes.end(), pChildNode );
    if ( it != m_childNodes.end() )
    {
        return false;
    }

    m_childNodes.push_back( pChildNode );
    return true;
}
