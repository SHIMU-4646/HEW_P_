#include "Goal.h"
#include "Geometory.h"
#include "Defines.h"

Goal::Goal()
	:m_pos()
	,m_time()
	, m_scale()
{

}

Goal::~Goal()
{

}

void Goal::Update()
{
	m_time += 1.0f/ FPS;
}

void Goal::Draw()
{
	// •ÏŠ·s—ñ‚ÌŒvZ
	DirectX::XMMATRIX T =
		DirectX::XMMatrixTranslation(m_pos[0], m_pos[1], m_pos[2]);
	DirectX::XMMATRIX Rx =
		DirectX::XMMatrixRotationX(m_time);
	DirectX::XMMATRIX Ry =
		DirectX::XMMatrixRotationY(m_time);
	DirectX::XMMATRIX Rz =
		DirectX::XMMatrixRotationZ(m_time);
	DirectX::XMMATRIX R =	Rx * Ry * Rz; // ‰ñ“]s—ñ‚Ì‚İŠ|‚¯‡‚í‚¹
	DirectX::XMMATRIX S =
		DirectX::XMMatrixScaling(m_scale[0], m_scale[1], m_scale[2]);
	DirectX::XMMATRIX mat = S * Rx * Ry * Rz * T;

	// •ÏŠ·s—ñ‚ğGPU‚É“n‚·‚½‚ß‚Ì‘Oˆ—
	mat = DirectX::XMMatrixTranspose(mat);
	DirectX::XMFLOAT4X4 fMat;
	DirectX::XMStoreFloat4x4(&fMat, mat);

	// •`‰æˆ—
	Geometory::SetWorld(fMat);
	Geometory::DrawBox();
}

void Goal::SetPos(float x, float y, float z)
{
	m_pos[0] = x;
	m_pos[1] = y;
	m_pos[2] = z;
}

// Šg‘å—¦‚Ìİ’è
void Goal::SetScale(float x, float y, float z)
{
	m_scale[0] = x;
	m_scale[1] = y;
	m_scale[2] = z;
}
