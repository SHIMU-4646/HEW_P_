#include "Ground.h"
#include "Geometory.h"





Ground::Ground()
	:m_pos()
	,m_scale()
{
}

Ground::~Ground()
{
}

void Ground::Update()
{

}

void Ground::Draw()
{
	// 変換行列の計算
	DirectX::XMMATRIX T =
		DirectX::XMMatrixTranslation(m_pos[0], m_pos[1], m_pos[2]);
	DirectX::XMMATRIX S =
		DirectX::XMMatrixScaling(m_scale[0], m_scale[1], m_scale[2]);
	DirectX::XMMATRIX mat = S * T;

	// 変換行列をGPUに渡すための前処理
	mat = DirectX::XMMatrixTranspose(mat);
	DirectX::XMFLOAT4X4 fMat;
	DirectX::XMStoreFloat4x4(&fMat, mat);

	// 描画処理
	Geometory::SetWorld(fMat);
	Geometory::DrawBox();
}

// 座標の設定
void Ground::SetPos(float x, float y, float z)
{
	m_pos[0] = x;
	m_pos[1] = y;
	m_pos[2] = z;
}

// 拡大率の設定
void Ground::SetScale(float x, float y, float z)
{
	m_scale[0] = x;
	m_scale[1] = y;
	m_scale[2] = z;
}

