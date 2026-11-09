// Enemy.cpp
#include "Enemy.h"
#include "Geometory.h"
#include "Defines.h"
#define ENEMY_MOVESPEED 7.5f

Enemy::Enemy()
	:m_position(0.0f, 0.0f, 0.0f)
	, m_rotation(0.0f, 0.0f, 0.0f)
	, m_scale(1.5f, 1.0f, 0.5f)
	, m_moveSpeed(ENEMY_MOVESPEED / FPS)
	, m_SPPosition(0.0f, 0.0f, 0.0f)
{
	m_collision.type = Collision::eBox;
	m_collision.box =
	{
		m_position,
		m_scale
	};

	m_SPCollision.type = Collision::eBox;
	m_SPCollision.box = 
	{
		m_SPPosition,
		m_scale
	};
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	// 障害物を手前に移動
	m_position.z += m_moveSpeed;
	
	m_collision.box.center = m_position;
}

void Enemy::SPUpdate()
{
	// 障害物を手前に移動
	m_SPPosition.z += m_moveSpeed / 3;
	m_SPCollision.box.center = m_SPPosition;
}

void Enemy::Draw()
{
	DirectX::XMMATRIX scale =
		DirectX::XMMatrixScaling(
			m_scale.x,
			m_scale.y,
			m_scale.z
		);


	DirectX::XMMATRIX rotation =
		DirectX::XMMatrixRotationRollPitchYaw(
			m_rotation.x,
			m_rotation.y,
			m_rotation.z
		);

	DirectX::XMMATRIX translation =
		DirectX::XMMatrixTranslation(
			m_position.x,
			m_position.y,
			m_position.z
		);

	DirectX::XMMATRIX enemyBox =
		scale * rotation * translation;


	enemyBox = DirectX::XMMatrixTranspose(enemyBox);

	// 読み取りデータに変換
	DirectX::XMFLOAT4X4 enemyBoxMatrix;
	DirectX::XMStoreFloat4x4(&enemyBoxMatrix, enemyBox);


	Geometory::SetWorld(enemyBoxMatrix);
	Geometory::DrawBox();

}

void Enemy::SPDraw()
{
	DirectX::XMMATRIX scale =
		DirectX::XMMatrixScaling(
			m_scale.x,
			m_scale.y,
			m_scale.z
		);


	DirectX::XMMATRIX rotation =
		DirectX::XMMatrixRotationRollPitchYaw(
			m_rotation.x,
			m_rotation.y,
			m_rotation.z
		);

	DirectX::XMMATRIX translationSP =
		DirectX::XMMatrixTranslation(
			m_SPPosition.x,
			m_SPPosition.y,
			m_SPPosition.z
		);

	DirectX::XMMATRIX SPEnemyBox =
		scale * rotation * translationSP;

	SPEnemyBox = DirectX::XMMatrixTranspose(SPEnemyBox);

	// 読み取りデータに変換
	DirectX::XMFLOAT4X4 SPEnemyBoxMatrix;
	DirectX::XMStoreFloat4x4(&SPEnemyBoxMatrix, SPEnemyBox);

	Geometory::SetWorld(SPEnemyBoxMatrix);
	Geometory::DrawBox();
}


// 生存状態関数
bool Enemy::IsDead()
{
	return m_position.z > 2.0f;
}

// 生存状態関数SP版
bool Enemy::IsSPDead()
{
	if (m_SPPosition.z > 2.0f)
	{
		return true;
	}
	return false;
}


void Enemy::SetPos(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void Enemy::SPSetPos(float x, float y, float z)
{
	m_SPPosition.x = x;
	m_SPPosition.y = y;
	m_SPPosition.z = z;
}

DirectX::XMFLOAT3 Enemy::GetPos()
{
	return m_position;
}

DirectX::XMFLOAT3 Enemy::SPGetPos()
{
	return m_SPPosition;
}

void Enemy::SetScaleX(float x)
{
	m_scale.x = x;

	m_collision.box.size.x = x;
	m_SPCollision.box.size.x = x;
}

float Enemy::GetScaleX()
{
	return m_scale.x;
}

Collision::Info Enemy::GetCollision() const
{
	return m_collision;
}

Collision::Info Enemy::GetSPCollision() const
{
	return m_SPCollision;
}