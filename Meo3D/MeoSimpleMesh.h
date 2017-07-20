#pragma once

#include <vector>
#include "MeoMath.h"


struct Vertex
{
	Float3 pos;
	Float4 color;
	Float2 uv;
};

class MeoSimpleMesh
{
public:
	MeoSimpleMesh();
	~MeoSimpleMesh();

	bool Initialize(ID3D11Device* pDevice);
	void Shutdown();

	void Render(ID3D11DeviceContext* pContext);

private:
	bool CreateVertexBuffer(ID3D11Device* pDevice);

	bool m_bInitialized = false;

	std::vector<Vertex> m_rawMeshData;
	std::vector<UINT> m_rawIndexData;

	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11Buffer* m_pIndexedBuffer = nullptr;

	size_t m_uVertexCount = 0;
	size_t m_uIndexCount = 0;
};

