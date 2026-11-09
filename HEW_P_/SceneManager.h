#pragma once
class SceneGame;

typedef enum
{
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_RESULT
}SCENE;

class SceneManager
{
private:
	SCENE scene;
	SceneGame *m_pSceneGame;

public:
	SceneManager();
	~SceneManager();

	void Update();
	void Draw();

	void ChangeScene(SCENE nextScene);
	int GetScene();
};