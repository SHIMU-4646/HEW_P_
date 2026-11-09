// Enemy.h
#pragma once
#include <DirectXMath.h>
#include "Collision.h"

class Enemy
{
private:
    DirectX::XMFLOAT3 m_position; // 早い障害物の位置
    DirectX::XMFLOAT3 m_SPPosition; // 遅い障害物の位置
    DirectX::XMFLOAT3 m_rotation;
    DirectX::XMFLOAT3 m_scale;

    float m_moveSpeed;

public:
    Enemy();
    ~Enemy();

    void Update();
    void SPUpdate();
    void Draw();
    void SPDraw();

    DirectX::XMFLOAT3 GetPos();
    DirectX::XMFLOAT3 SPGetPos();

    // 障害物が消えたか
    bool IsDead();
    bool IsSPDead();

    void SetPos(float x, float y, float z);
    void SPSetPos(float x, float y, float z);

    //  障害物の横幅サイズ設定関数
    void SetScaleX(float x);

    // 障害物の横幅サイズ取得関数
    float GetScaleX();

    Collision::Info GetCollision() const;
    Collision::Info GetSPCollision() const;

private:
    Collision::Info m_collision;
    Collision::Info m_SPCollision;
};