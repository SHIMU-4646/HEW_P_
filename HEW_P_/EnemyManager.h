// EnemyManager.h
#pragma once

#include "Enemy.h"
#define MAX_ENEMY 999

class EnemyManager
{
private:
	Enemy* m_pEnemy[MAX_ENEMY];
	Enemy* m_pSPEnemy[MAX_ENEMY];

	int m_spawnTimer;    // 障害物のスポーンタイマー
	int m_spawnInterval; // 障害物のスポーン間隔
	bool m_pKeyOld = false;
	bool m_KeyInterval = false;
	float m_waitKeyTimer;

public:
	EnemyManager();
	~EnemyManager();
	void Update(
		const DirectX::XMFLOAT3& playerPos,
		Collision::Info playerCollision
	);
	void Draw();

	void SpawnEnemy();
	void SPSpawnEnemy();
};