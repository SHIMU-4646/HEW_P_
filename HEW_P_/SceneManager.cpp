#include "SceneManager.h"
#include "SceneGame.h"

SceneManager::SceneManager()
	:scene(SCENE_TITLE)
{
	m_pSceneGame = new SceneGame();
}

SceneManager::~SceneManager()
{
	if (m_pSceneGame)
	{
		delete m_pSceneGame;
		m_pSceneGame = nullptr;
	}
}

void SceneManager::Update()
{
	switch (GetScene())
	{
	case SCENE_TITLE:

		break;
	case SCENE_GAME:
		m_pSceneGame->Update();
		break;
	case SCENE_RESULT:

		break;
	}
}

void SceneManager::Draw()
{
	switch (GetScene())
	{
	case SCENE_TITLE:
		break;
	case SCENE_GAME:
		m_pSceneGame->Draw();
		break;
	case SCENE_RESULT:
		break;
	}
}

void SceneManager::ChangeScene(SCENE nextScene)
{
	switch (scene)
	{
	case SCENE_TITLE:
		// シーンの終了処理
		
		break;
	case SCENE_GAME:
		// シーンの終了処理
		// m_pSceneGame->SceneGame::~SceneGame();

		break;
	case SCENE_RESULT:
		// シーンの終了処理
		break;
	}
	scene =  nextScene;

	switch (scene)
	{
	case SCENE_TITLE:
		// シーンの初期化処理
		break;
	case SCENE_GAME:
		// シーンの初期化処理
		// m_pSceneGame->SceneGame::SceneGame();
		break;
	case SCENE_RESULT:
		// シーンの初期化処理
		break;
	}
}

int SceneManager::GetScene()
{
	return scene;
}