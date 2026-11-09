#include "Player.h"
#include "Input.h"
#include "Defines.h"
#include "Geometory.h"

Player::Player()
    : m_pModel(nullptr)
    , m_pos(0.0f, 1.0f, 0.0f)
    , m_rot(0.0f, 0.0f, 0.0f)
    , m_scale(0.2f, 1.0f, 0.2f)
    , m_limit(3.0f)
{
    m_collision.type = Collision::eBox;
    m_collision.box =
    {
        m_pos,
        m_scale
    };
}

Player::~Player()
{
    delete m_pModel;
    m_pModel = nullptr;
}

bool Player::Init()
{
    // 今はFBXを使わず、ボックスを主人公にする
    return true;
}

void Player::Update()
{
    const float moveSpeed = METER(8.0f) / FPS;

    /*if (IsKeyPress('W'))
    {
        m_pos.z += moveSpeed;
    }

    if (IsKeyPress('S'))
    {
        m_pos.z -= moveSpeed;
    }*/

    if (IsKeyPress('D'))
    {
        m_pos.x -= moveSpeed;
    }

    if (IsKeyPress('A'))
    {
        m_pos.x += moveSpeed;
    }

    // プレイヤーの移動上限
    if (m_pos.x > m_limit)  // 右側
    {
        m_pos.x = m_limit;
    }

    if (m_pos.x < -m_limit) // 左側
    {
        m_pos.x = -m_limit;
    }

    m_collision.box.center = m_pos;
}

void Player::Draw()
{
    DirectX::XMMATRIX scale =
        DirectX::XMMatrixScaling(
            m_scale.x,
            m_scale.y,
            m_scale.z
        );

    DirectX::XMMATRIX rotation =
        DirectX::XMMatrixRotationRollPitchYaw(
            m_rot.x,
            m_rot.y,
            m_rot.z
        );

    DirectX::XMMATRIX translation =
        DirectX::XMMatrixTranslation(
            m_pos.x,
            m_pos.y,
            m_pos.z
        );

    DirectX::XMMATRIX world =
        scale * rotation * translation;

    // シェーダーへ渡す形式に転置
    world = DirectX::XMMatrixTranspose(world);

    DirectX::XMFLOAT4X4 worldMatrix;
    DirectX::XMStoreFloat4x4(
        &worldMatrix,
        world
    );

    Geometory::SetWorld(worldMatrix);
    Geometory::DrawBox();
}

void Player::SetPos(float x, float y, float z)
{
    m_pos = DirectX::XMFLOAT3(x, y, z);
}

DirectX::XMFLOAT3 Player::GetPos() const
{
    return m_pos;
}

Collision::Info Player::GetCollision() const
{
   return m_collision;
}

void Player::OnCollision(Collision::Result collision)
{
}
