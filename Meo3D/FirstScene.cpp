
#include "stdafx.h"
#include "FirstScene.h"
#include "Meo3D.h"
#include "MeoSimpleMesh.h"


void CreateFirstScene( const MeoRenderer* pMeoRenderer )
{
    MeoScene* pScene = pMeoRenderer->Scene();
    MeoSimpleMesh* pSimpleMesh1 = pScene->CreateSimpleMesh();



    std::vector<SimpleVertex> v1;
    std::vector<UINT> v2;
    pSimpleMesh1->Initialize(v1, v2);

}
