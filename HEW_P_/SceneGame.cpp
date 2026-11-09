#include "SceneGame.h"
#include "Geometory.h"
#include "CameraDebug.h"


SceneGame::SceneGame()
{
	SetDepthTest(DEPTH_ENABLE);
	m_pGround = new Ground;
	m_pGround->SetPos(0.0f, 0.0f, 0.0f);
	m_pGround->SetScale(3.0f, 0.4f, 3.0f);

	m_pGoal = new Goal;
	m_pGoal->SetPos(0.0f, 1.0f, 0.0f);
	m_pGoal->SetScale(0.5f, 0.5f, 0.5f);



	m_pModel = new Model();

	/*if (!m_pModel->Load("./Assets/Model/tree_forest.fbx",0.5f,Model::Flip::None))
	{
		MessageBox(NULL, "tree_forest.fbx", "File Load Error", MB_OK);
	}*/
	//  
	m_pPlayer = new Player();
	m_pPlayer->Init();
	m_pPlayer->SetPos(0.0f, 0.5f, 0.0f);

	DirectX::XMFLOAT3 playerPos = m_pPlayer->GetPos();

	m_pCamera = new CameraDebug();
	m_pCamera->SetLook(playerPos.x, playerPos.y + 1.0f, playerPos.z - 1.0f);

	m_pEnemyManager = new EnemyManager();

}

SceneGame::~SceneGame()
{
	if (m_pEnemyManager)
	{
		delete m_pEnemyManager;
		m_pEnemyManager = nullptr;
	}

	if (m_pGround)
	{
		delete m_pGround;
		m_pGround = nullptr;
	}

	if (m_pGoal)
	{
		delete m_pGoal;
		m_pGoal = nullptr;
	}

	if (m_pCamera)
	{
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pModel)
	{
		delete m_pModel;
		m_pModel = nullptr;
	}

	if (m_pPlayer)
	{
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}
}



void SceneGame::Update()
{

	m_pGround->Update();
	m_pGoal->Update();
	m_pPlayer->Update();
	m_pCamera->Update();
	m_pEnemyManager->Update(
		m_pPlayer->GetPos(),
		m_pPlayer->GetCollision()
	);

}
void SceneGame::Draw()
{
	// 仮置きボックスを描画する前にカメラを設定
	Geometory::SetView(m_pCamera->GetViewMatrix());
	Geometory::SetProjection(m_pCamera->GetProjectionMatrix());


	//m_pGround->Draw();
	//dm_pGoal->Draw();

	m_pEnemyManager->Draw();
	m_pPlayer->Draw();

	//Geometory::DrawBox();

	//Geometory::DrawSphere();
	//Geometory::DrawCylinder();

	if (m_pModel)
	{
		m_pModel->Draw();
	}

}
