#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__

#include "Scene.h"
#include "Ground.h"
#include "Goal.h"
#include "Camera.h"
#include "Model.h"
#include "Player.h"
#include "EnemyManager.h"

class SceneGame : public Scene
{
public:
	SceneGame();
	~SceneGame();
	void Update() final;
	void Draw() final;

private:
	Ground* m_pGround; // 地面オブジェクト
	Goal* m_pGoal;	   // ゴールオブジェクト
	Camera* m_pCamera; // ゲーム中に動かすカメラ
	Model* m_pModel;   // モデル
	Player* m_pPlayer; // プレイヤー
	EnemyManager* m_pEnemyManager;   // 障害物
};

#endif // __SCENE_GAME_H__