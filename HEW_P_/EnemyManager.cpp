// EnemyManager.cpp
#include <cmath>
#include <algorithm>

#include "EnemyManager.h"
#include "Defines.h"

using namespace std;


EnemyManager::EnemyManager()
    : m_spawnTimer(0)
    , m_spawnInterval(FPS)
    , m_KeyInterval(false)
    , m_pKeyOld(false)
    , m_waitKeyTimer(0.5)
{
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        m_pEnemy[i] = nullptr;
        m_pSPEnemy[i] = nullptr;
    }
}

EnemyManager::~EnemyManager()
{
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        if (m_pEnemy[i] != nullptr)
        {
            delete m_pEnemy[i];
            m_pEnemy[i] = nullptr;
        }

        if (m_pSPEnemy[i] != nullptr)
        {
            delete m_pSPEnemy[i];
            m_pSPEnemy[i] = nullptr;
        }
    }
}

void EnemyManager::Update(const DirectX::XMFLOAT3& playerPos,
    Collision::Info playerCollision)
{
    m_spawnTimer++;

    if (m_spawnTimer >= m_spawnInterval)
    {
        SpawnEnemy();
        SPSpawnEnemy();
        m_spawnTimer = 0;
    }

    if (m_KeyInterval)
    {
        m_waitKeyTimer++;
        if (m_waitKeyTimer >= 60)
        {
            m_KeyInterval = false;
            m_waitKeyTimer = 0.5f;
        }
    }

    // 削るキー
    const bool pKey = (GetAsyncKeyState('P') & 0x8000) != 0; // By.GoogleChrome： (GetAsyncKeyState('キー') & 0x8000) != 0　でキー指定

    if (pKey && !m_pKeyOld && !m_KeyInterval)
    {
        // 敵とプレイヤーのX座標の許容範囲
        float xRange = 0.75f;
        // 削る量
        float cutSize = 0.95f;
        // 最小の削り幅（削りまくった後に最小の残す大きさ）
        float cutMinSize = 0.0f;

        for (int i = 0; i < MAX_ENEMY; i++)
        {
            if (m_pEnemy[i] == nullptr)
            {
                continue;
            }

            DirectX::XMFLOAT3 pos = m_pEnemy[i]->GetPos();

            // 敵とプレイヤーのX座標の差を比較
            // XRange以内であれば削る
            if (fabs(pos.x - playerPos.x) <= xRange && (pos.z >= -3.0f && pos.z <= 0.0f)) // fabsは絶対値をreturn
            {
                // 削る前の敵のサイズを取得
                float oldSizeX = m_pEnemy[i]->GetScaleX();

                // 削った後の大きさを計算
                float newSizeX = oldSizeX - cutSize;

                if (newSizeX < cutMinSize)
                {
                    delete m_pEnemy[i];
                    m_pEnemy[i] = nullptr;
                }

                if (m_pEnemy[i] == nullptr)
                {
                    continue;
                }

                // 削られた量を計算
                float removedSize = oldSizeX - newSizeX;

                float moveSide = removedSize * 0.5f;

                if (playerPos.x > pos.x)
                {
                    moveSide = -moveSide;
                }

                // 計算した大きさに障害物を設定
                m_pEnemy[i]->SetScaleX(newSizeX);
                // 位置を動かすことで削った感を出す
                m_pEnemy[i]->SetPos(pos.x + moveSide, pos.y, pos.z);

                // １秒間のキー入力待機
                m_KeyInterval = true;
            }
        }

        for (int i = 0; i < MAX_ENEMY; i++)
        {
            if (m_pSPEnemy[i] == nullptr)
            {
                continue;
            }

            DirectX::XMFLOAT3 pos = m_pSPEnemy[i]->SPGetPos();

            // 敵とプレイヤーのX座標の差を比較
            // XRange以内であれば削る
            if (fabs(pos.x - playerPos.x) <= xRange && (pos.z >= -3.0f && pos.z <= 0.0f)) // fabsは絶対値をreturn
            {
                // 削る前の敵のサイズを取得
                float oldSizeX = m_pSPEnemy[i]->GetScaleX();

                // 削った後の大きさを計算
                float newSizeX = oldSizeX - cutSize;

                if (newSizeX < cutMinSize)
                {
                    delete m_pSPEnemy[i];
                    m_pSPEnemy[i] = nullptr;
                }

                if (m_pSPEnemy[i] == nullptr)
                {
                    continue;
                }

                // 削られた量を計算
                float removedSize = oldSizeX - newSizeX;

                float moveSide = removedSize * 0.5f;

                if (playerPos.x > pos.x)
                {
                    moveSide = -moveSide;
                }

                // 計算した大きさに障害物を設定
                m_pSPEnemy[i]->SetScaleX(newSizeX);
                // 位置を動かすことで削った感を出す
                m_pSPEnemy[i]->SPSetPos(pos.x + moveSide, pos.y, pos.z);

                // １秒間のキー入力待機
                m_KeyInterval = true;
            }
        }
    }

    // 押した状態を検知
    m_pKeyOld = pKey;

   
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        if (m_pEnemy[i] != nullptr)
        {
            m_pEnemy[i]->Update();

            Collision::Result result =
                Collision::Hit(
                    playerCollision,
                    m_pEnemy[i]->GetCollision()
                );

            if (result.isHit)
            {
                // 通常障害物に当たった
                OutputDebugStringA("通常障害物に当たった\n");
            }

            if (m_pEnemy[i]->IsDead())
            {
                delete m_pEnemy[i];
                m_pEnemy[i] = nullptr;
            }
        }

        if (m_pSPEnemy[i] != nullptr)
        {
            m_pSPEnemy[i]->SPUpdate();

            Collision::Result result =
                Collision::Hit(
                    playerCollision,
                    m_pSPEnemy[i]->GetSPCollision()
                );

            if (result.isHit)
            {
                // SP障害物に当たった
                
                OutputDebugStringA("SP障害物に当たった\n");
            }

            if (m_pSPEnemy[i]->IsSPDead())
            {
                delete m_pSPEnemy[i];
                m_pSPEnemy[i] = nullptr;
            }
        }
    }
    
}

void EnemyManager::Draw()
{
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        if (m_pEnemy[i] != nullptr)
        {
            m_pEnemy[i]->Draw();
        }
        if (m_pSPEnemy[i] != nullptr)
        {
            m_pSPEnemy[i]->SPDraw();
        }
    }
}

void EnemyManager::SpawnEnemy()
{
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        if (m_pEnemy[i] == nullptr)
        {
            // 乱数でスポーン場所をランダム化(Main.cppで
            // リアルタイム乱数実装済み)
            float x = (rand() % 61 - 30) / 10.0f;
            float y = 1.0f;
            float z = -15.0f;

            m_pEnemy[i] = new Enemy();
            m_pEnemy[i]->SetPos(x, y, z);

            break;
        }
    }
}

void EnemyManager::SPSpawnEnemy()
{
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        if (m_pSPEnemy[i] == nullptr)
        {
            // 乱数でスポーン場所をランダム化(Main.cppで
            // リアルタイム乱数実装済み)
            float x = (rand() % 61 - 30) / 10.0f;
            float y = 1.0f;
            float z = -15.0f;

            m_pSPEnemy[i] = new Enemy();
            m_pSPEnemy[i]->SPSetPos(x, y, z);

            break;
        }
    }
}
