#pragma once
#include "DirectXMath.h"

class Collision
{
public:
	// --- あたり判定形状の種類
	enum Type
	{
		eNone,
		eBox,
		eSphere,
		ePlane,
		eRay,
		eLine,
		ePoint,
		eTraiangle,
	};

	// --- あたり判定の形状
	struct Box	
	{
		DirectX::XMFLOAT3 center; // 中心座標
		DirectX::XMFLOAT3 size; // サイズ
	};

	struct Sphere
	{
		DirectX::XMFLOAT3 center; // 中心座標
		float radius; // 半径
	};

	struct Plane
	{
		DirectX::XMFLOAT3 pos; // 平面上の1点
		DirectX::XMFLOAT3 normal; //平面上の法線
	};

	struct Ray
	{
		DirectX::XMFLOAT3 origin; // 始点
		DirectX::XMFLOAT3 dir; // レイの向き
	};

	struct Line
	{
		DirectX::XMFLOAT3 start; //線分の支店
		DirectX::XMFLOAT3 end; // 線分の終点
	};

	struct Point
	{
		DirectX::XMFLOAT3 pos; // 座標
	};

	struct Triangle
	{
		DirectX::XMFLOAT3 point[3]; // 頂点
	};

	// ---あたり判定の統合情報
	struct Info
	{
		Type type;
		union
		{
			Box box;
			Sphere sphere;
			Plane plane;
			Ray ray;
			Line line;
			Point point;
			Triangle triangle;
		};
	};

	//--- あたり判定の結果
	struct Result
	{
		bool isHit; // 当たったかどうか
		DirectX::XMFLOAT3 point; // ヒット位置
		DirectX::XMFLOAT3 normal; // ヒット平面
		Info other; //あたり判定オブジェクト

	};

public:
	// Info型でのあたり判定
	static Result Hit(Info a, Info b);
	

	// 四角同士のあたり判定
	static Result Hit(Box a, Box b);

	// 弾同士のあたり判定
	static Result Hit(Sphere a, Sphere b);

	static Result Hit(Plane plane, Ray ray, float length);

	static Result Hit(Plane plane, Line line);

	static Result Hit(Point point, Triangle triangle);
};