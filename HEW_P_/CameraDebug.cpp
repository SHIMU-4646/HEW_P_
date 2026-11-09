#include "CameraDebug.h"
#include "Input.h"
#include "Defines.h"



#define CAMERA_RAD (1.0f)
#define CAMERA_RADIUS (0.1f)

// コンストラクタ
CameraDebug::CameraDebug()
	: m_radXZ(0.0f)
	, m_radY(15.0f)
	,m_radius(5.0f)
{
}

// デストラクタ
CameraDebug::~CameraDebug()
{
}

// 更新処理
void CameraDebug::Update()
{
	// キー入力に合わせた注視点の移動処理 // ↑↓←→,SHIFT,CTRL
	// 一秒間の移動距離から１フレームの痩躯度が計算できるとよい
	const float lookspeed = METER(5.0f)/ FPS;
	if (IsKeyPress(VK_UP))     {m_look.z -= lookspeed;}
	if (IsKeyPress(VK_DOWN))   {m_look.z += lookspeed;}
	if (IsKeyPress(VK_LEFT))   {m_look.x += lookspeed;}
	if (IsKeyPress(VK_RIGHT))  {m_look.x -= lookspeed;}
	if (IsKeyPress(VK_SHIFT))  {m_look.y += lookspeed;}
	if (IsKeyPress(VK_CONTROL)){m_look.y -= lookspeed;}

	// 回り込みの処理　// WASD
	constexpr float radspeed = DirectX::XMConvertToRadians(1.0f);
	//if (IsKeyPress('A')){m_radXZ += DirectX::XMConvertToRadians(CAMERA_RAD);}
	//if (IsKeyPress('D')){m_radXZ -= DirectX::XMConvertToRadians(CAMERA_RAD);}
	//if (IsKeyPress('W')){m_radY += DirectX::XMConvertToRadians(CAMERA_RAD);}
	//if (IsKeyPress('S')){m_radY -= DirectX::XMConvertToRadians(CAMERA_RAD);}

	// カメラの距離を変える処理 // QERT
	if (IsKeyPress('Q')) // 拡大
	{
		m_radius += CAMERA_RADIUS;
	}

	if (IsKeyPress('E')) // 拡大
	{
		m_radius -= CAMERA_RADIUS;

		if (m_radius < CAMERA_RADIUS)
		{
			m_radius = CAMERA_RADIUS;
		}
	}

	if (IsKeyPress('R')) // 急速縮小
	{
		m_radius += CAMERA_RADIUS;
	}

	if (IsKeyPress('T')) // 急速拡大
	{
		m_radius -= CAMERA_RADIUS;

		if (m_radius < CAMERA_RADIUS)
		{
			m_radius = CAMERA_RADIUS;
		}
	}

	// カメラ位置の計算
	m_pos.x = cosf(m_radY) * -sinf(m_radXZ) * m_radius + m_look.x;
	m_pos.y = sinf(m_radY) *                  m_radius + m_look.y;
	m_pos.z = cosf(m_radY) * -cosf(m_radXZ) * m_radius + m_look.z;
}