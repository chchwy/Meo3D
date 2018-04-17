#pragma once

#include <vector>

class MeoScene;


struct SimpleVertex
{
	Float3 pos;
	Float4 color;
	Float2 uv;
};

class MeoSimpleMesh
{
public:
	MeoSimpleMesh( ID3D11Device* pDevice );
	~MeoSimpleMesh();

	bool Initialize(const std::vector<SimpleVertex>& vVertexData, 
                    const std::vector<UINT>& vIndexData );
	void Shutdown();
	void Render(ID3D11DeviceContext* pContext);
    void SetScene(MeoScene* sc);

private:
	bool CreateVertexBuffer(ID3D11Device* pDevice);

	bool m_bInitialized = false;

	std::vector<SimpleVertex> m_rawMeshData;
	std::vector<UINT> m_rawIndexData;

	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11Buffer* m_pIndexedBuffer = nullptr;

	size_t m_uVertexCount = 0;
	size_t m_uIndexCount = 0;

    ID3D11Device* m_pDevice = nullptr;
    MeoScene* m_pScene = nullptr;
};

