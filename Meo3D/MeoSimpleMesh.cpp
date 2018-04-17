#include "stdafx.h"
#include "MeoSimpleMesh.h"
#include <iostream>

MeoSimpleMesh::MeoSimpleMesh( ID3D11Device* pDevice )
{
    m_pDevice = pDevice;
}

MeoSimpleMesh::~MeoSimpleMesh()
{
    Shutdown();
}

bool MeoSimpleMesh::Initialize(const std::vector<SimpleVertex>& vVertexData,
                               const std::vector<UINT>& vIndexData )
{
	m_vOrigMeshData = vVertexData;
	m_uVertexCount = vVertexData.size();

    m_vOrigIndexData = vIndexData;
	m_uIndexCount = vIndexData.size();

	m_bInitialized = CreateVertexBuffer(m_pDevice);
    assert(m_bInitialized);
    return m_bInitialized;
}

void MeoSimpleMesh::Shutdown()
{
	SAFE_RELEASE(m_pIndexedBuffer);
	SAFE_RELEASE(m_pVertexBuffer);
}

void MeoSimpleMesh::Render(ID3D11DeviceContext* pContext)
{
    if (m_bInitialized)
    {
        UINT stride = sizeof(SimpleVertex);
        UINT offset = 0;
        pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
        pContext->IASetIndexBuffer(m_pIndexedBuffer, DXGI_FORMAT_R32_UINT, 0);
        pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        pContext->DrawIndexed(m_uIndexCount, 0, 0);
    }
}

void MeoSimpleMesh::SetScene(MeoScene* sc)
{
    assert(sc);
    m_pScene = sc;
}

bool MeoSimpleMesh::CreateVertexBuffer(ID3D11Device* pDevice)
{
	HRESULT hr;

	D3D11_BUFFER_DESC vDesc; // vertex buffer
	vDesc.Usage = D3D11_USAGE_DEFAULT;
	vDesc.ByteWidth = sizeof(SimpleVertex) * 3;
	vDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vDesc.CPUAccessFlags = 0;
	vDesc.MiscFlags = 0;
	vDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vData;
	vData.pSysMem = m_vOrigMeshData.data();
	vData.SysMemPitch = 0;
	vData.SysMemSlicePitch = 0;

	hr = pDevice->CreateBuffer(&vDesc, &vData, &m_pVertexBuffer);
	if (FAILED(hr))
	{
		std::cout << "Failed to create vertex buffer.";
	}

	D3D11_BUFFER_DESC iDesc; // index buffer
							 // Set up the description of the static index buffer.
	iDesc.Usage = D3D11_USAGE_DEFAULT;
	iDesc.ByteWidth = sizeof(UINT) * 3;
	iDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	iDesc.CPUAccessFlags = 0;
	iDesc.MiscFlags = 0;
	iDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	D3D11_SUBRESOURCE_DATA iData;
	iData.pSysMem = m_vOrigIndexData.data();
	iData.SysMemPitch = 0;
	iData.SysMemSlicePitch = 0;

	// Create the index buffer.
	hr = pDevice->CreateBuffer(&iDesc, &iData, &m_pIndexedBuffer);
	if (FAILED(hr))
	{
		std::cout << "Failed to create index buffer.";
	}

	return true;
}
