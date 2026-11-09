#pragma once
#include "DirectXMath.h"
//#include "DirectX.h"


class Goal
{
private:
	float m_pos[3]; // 座標
	float m_time;	// アニメーション経過時間
	float m_scale[3]; // 拡大率

public:
	Goal();
	~Goal();

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

	// 座標の設定
	void SetPos(float x, float y, float z);

	void SetScale(float x, float y, float z);
};