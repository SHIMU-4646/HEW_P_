#pragma once

#include <DirectXMath.h>
#include "Model.h"
#include "Collision.h"

class Player
{
public:
    Player();
    ~Player();

    bool Init();
    void Update();
    void Draw();

    void SetPos(float x, float y , float z);
    DirectX::XMFLOAT3 GetPos() const;

    Collision::Info GetCollision() const;
    void OnCollision(Collision::Result collision);

private:
    Model* m_pModel;

    DirectX::XMFLOAT3 m_pos;
    DirectX::XMFLOAT3 m_rot;
    DirectX::XMFLOAT3 m_scale;
    float m_limit;

    Collision::Info m_collision;
};