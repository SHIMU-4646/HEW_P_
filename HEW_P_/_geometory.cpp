#include "Geometory.h"
#include <stdio.h>

void Geometory::MakeBox()
{
	//--- 頂点の作成
	Vertex vtx[] = {

		{{-0.5f, 0.5f,-0.5f},{0.0f,0.0f}},  //  0 // オモテ
		{{ 0.5f, 0.5f,-0.5f},{1.0f,0.0f}},  //  1
		{{-0.5f,-0.5f,-0.5f},{0.0f,1.0f}},	//  2
		{{ 0.5f,-0.5f,-0.5f},{1.0f,1.0f}},	//  3

		{{ 0.5f, 0.5f, 0.5f},{0.0f,0.0f}},  //  4 // ウラ
		{{-0.5f, 0.5f, 0.5f},{1.0f,0.0f}},  //  5
		{{ 0.5f,-0.5f, 0.5f},{0.0f,1.0f}},	//  6
		{{-0.5f,-0.5f, 0.5f},{1.0f,1.0f}},	//  7

		{{-0.5f, 0.5f, 0.5f},{0.0f,0.0f}},  //  8 // ヒダリ
		{{-0.5f, 0.5f,-0.5f},{1.0f,0.0f}},  //  9
		{{-0.5f,-0.5f, 0.5f},{0.0f,1.0f}},	// 10
		{{-0.5f,-0.5f,-0.5f},{1.0f,1.0f}},	// 11

		{{ 0.5f, 0.5f,-0.5f},{0.0f,0.0f}},  // 12 // ミギ
		{{ 0.5f, 0.5f, 0.5f},{1.0f,0.0f}},  // 13
		{{ 0.5f,-0.5f,-0.5f},{0.0f,1.0f}},	// 14
		{{ 0.5f,-0.5f, 0.5f},{1.0f,1.0f}},	// 15

		{{-0.5f, 0.5f, 0.5f},{0.0f,0.0f}},  // 16 // ウエ
		{{ 0.5f, 0.5f, 0.5f},{1.0f,0.0f}},  // 17
		{{-0.5f, 0.5f,-0.5f},{0.0f,1.0f}},	// 18
		{{ 0.5f, 0.5f,-0.5f},{1.0f,1.0f}},	// 19

		{{ 0.5f,-0.5f, 0.5f},{0.0f,0.0f}},  // 20 // シタ
		{{-0.5f,-0.5f, 0.5f},{1.0f,0.0f}},  // 21
		{{ 0.5f,-0.5f,-0.5f},{0.0f,1.0f}},	// 22
		{{-0.5f,-0.5f,-0.5f},{1.0f,1.0f}},	// 23



	};

	//--- インデックスの作成
	int idx[] = {
		 0, 1, 2,  1, 3, 2,	// オモテ
		 4, 5, 6,  5, 7, 6,	// ウラ
		 8, 9,10,  9,11,10, // ヒダリ
		12,13,14, 13,15,14, // ミギ
		16,17,18, 17,19,18, // ウエ
		20,21,22, 21,23,22, // シタ
	};

	// バッファの作成
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;										// 頂点のデータ
	desc.vtxCount = _countof(vtx);							// 頂点の数
	desc.vtxSize = sizeof(Vertex);							// 頂点一つあたりのデータサイズ
	desc.pIdx = idx;										// インデックスのデータ
	desc.idxCount = _countof(idx);							// インデックスの数
	desc.idxSize = sizeof(int);								// インデックス一つあたりのデータサイズ
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;	// 直方体表示用のトポロジー

	//
	m_pBox = new MeshBuffer();
	m_pBox->Create(desc);
}

void Geometory::MakeCylinder()
{
	const int CIRCLE_NUM = 8;
	const float PI = 3.14159265f;

	//--- 頂点の作成
	Vertex vtx[36] = {};

	// 天面
	for (int i = 0; i <= CIRCLE_NUM; i++)
	{
		float rad = 2.0f * PI * i / CIRCLE_NUM;

		float x = cosf(rad) * 0.5f;
		float z = sinf(rad) * 0.5f;

		vtx[i] =
		{
			{x, 0.5f, z},
			{x + 0.5f, z + 0.5f}
		};
	}

	// 底面
	for (int i = 0; i <= CIRCLE_NUM; i++)
	{
		float rad = 2.0f * PI * i / CIRCLE_NUM;

		float x = cosf(rad) * 0.5f;
		float z = sinf(rad) * 0.5f;

		vtx[9 + i] =
		{
			{x, -0.5f, z},
			{x + 0.5f, z + 0.5f}
		};
	}

	// 側面
	for (int i = 0; i <= CIRCLE_NUM; i++)
	{
		float rad = 2.0f * PI * i / CIRCLE_NUM;

		float x = cosf(rad) * 0.5f;
		float z = sinf(rad) * 0.5f;

		float u = (float)i / CIRCLE_NUM;

		// 上側
		vtx[18 + i * 2] =
		{
			{x, 0.5f, z},
			{u, 0.0f}
		};

		// 下側
		vtx[18 + i * 2 + 1] =
		{
			{x, -0.5f, z},
			{u, 1.0f}
		};
	};


	//--- インデックスの作成
	int idx[84] = {};

	int index = 0;

	// 天面
	for (int i = 1; i < CIRCLE_NUM - 1; i++)
	{
		idx[index++] = 0;
		idx[index++] = i + 1;
		idx[index++] = i;
	}

	// 底面
	for (int i = 1; i < CIRCLE_NUM - 1; i++)
	{
		idx[index++] = 9;
		idx[index++] = 9 + i;
		idx[index++] = 9 + i + 1;
	}

	// 側面
	for (int i = 0; i < CIRCLE_NUM; i++)
	{
		int top1 = 18 + i * 2;
		int bottom1 = top1 + 1;

		int top2 = top1 + 2;
		int bottom2 = top1 + 3;

		idx[index++] = top1;
		idx[index++] = top2;
		idx[index++] = bottom1;

		idx[index++] = top2;
		idx[index++] = bottom2;
		idx[index++] = bottom1;
	}


	// バッファの作成
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;										// 頂点のデータ
	desc.vtxCount = _countof(vtx);							// 頂点の数
	desc.vtxSize = sizeof(Vertex);							// 頂点一つあたりのデータサイズ
	desc.pIdx = idx;										// インデックスのデータ
	desc.idxCount = _countof(idx);							// インデックスの数
	desc.idxSize = sizeof(int);								// インデックス一つあたりのデータサイズ
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;	// 円柱表示用のトポロジー

	//
	m_pCylinder = new MeshBuffer();
	m_pCylinder->Create(desc);
}

void Geometory::MakeSphere()
{
	const int CIRCLE_NUM = 16;
	const float PI = 3.14159265f;

	//--- 頂点の作成
	Vertex vtx[(CIRCLE_NUM + 1) * (CIRCLE_NUM + 1)] = {};

	for (int y = 0; y <= CIRCLE_NUM; y++)
	{
		// 縦方向の角度
		float angleB = PI * y / CIRCLE_NUM;

		for (int x = 0; x <= CIRCLE_NUM; x++)
		{
			// 横方向の角度
			float angleA = 2.0f * PI * x / CIRCLE_NUM;

			float px = sinf(angleB) * cosf(angleA) * 0.5f;
			float py = cosf(angleB) * 0.5f;
			float pz = sinf(angleB) * sinf(angleA) * 0.5f;

			float u = (float)x / CIRCLE_NUM;
			float v = (float)y / CIRCLE_NUM;

			int num = y * (CIRCLE_NUM + 1) + x;

			vtx[num] =
			{
				{px, py, pz},
				{u, v}
			};
		}
	}


	//--- インデックスの作成
	int idx[CIRCLE_NUM * CIRCLE_NUM * 6] = {};

	int index = 0;

	for (int y = 0; y < CIRCLE_NUM; y++)
	{
		for (int x = 0; x < CIRCLE_NUM; x++)
		{
			int topLeft =
				y * (CIRCLE_NUM + 1) + x;

			int topRight =
				topLeft + 1;

			int bottomLeft =
				(y + 1) * (CIRCLE_NUM + 1) + x;

			int bottomRight =
				bottomLeft + 1;

			idx[index++] = topLeft;
			idx[index++] = topRight;
			idx[index++] = bottomLeft;

			idx[index++] = topRight;
			idx[index++] = bottomRight;
			idx[index++] = bottomLeft;
		}
	}


	// バッファの作成
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;										// 頂点のデータ
	desc.vtxCount = _countof(vtx);							// 頂点の数
	desc.vtxSize = sizeof(Vertex);							// 頂点一つあたりのデータサイズ
	desc.pIdx = idx;										// インデックスのデータ
	desc.idxCount = _countof(idx);							// インデックスの数
	desc.idxSize = sizeof(int);								// インデックス一つあたりのデータサイズ
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;	// 球表示用のトポロジー

	//
	m_pSphere = new MeshBuffer();
	m_pSphere->Create(desc);
}