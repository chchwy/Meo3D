
#include "stdafx.h"
#include "FirstScene.h"
#include "Meo3D.h"
#include "MeoSimpleMesh.h"


void CreateFirstScene( const MeoRenderer* pMeoRenderer )
{
    MeoScene* pScene = pMeoRenderer->Scene();
    MeoSimpleMesh* pSimpleMesh1 = pScene->CreateSimpleMesh();

    std::vector<SimpleVertex> v1(3);
    v1[0].pos = { -1, -1, 0 };
    v1[0].color = { 1, 0, 0, 1 };

    v1[1].pos = { 1, -1, 0 };
    v1[1].color = { 0, 1, 0, 1 };

    v1[2].pos = { -1, 1, 0 };
    v1[2].color = { 0, 0, 1, 1 };

    std::vector<UINT> v2(3);
    v2[0] = 2;
    v2[1] = 1;
    v2[2] = 0;

    pSimpleMesh1->Initialize(v1, v2);

}
