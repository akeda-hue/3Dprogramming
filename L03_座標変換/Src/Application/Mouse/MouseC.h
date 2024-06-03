#pragma once

class C_Mouse
{
//変数
private:
	POINT mousePos;

//関数
public:
	void Init();

	POINT GetMousePos();

	bool IsInsideBox(Math::Vector2 a_pos,float a_halfHeight,float a_halfWidth);

	float CalcDeg(Math::Vector2 a_pos);

//コンストラクタ＆デストラクタ
private:
	C_Mouse(){}
	~C_Mouse() {}

public:
	static C_Mouse& GetInstance()
	{
		static C_Mouse instance;
		return instance;
	}
};

#define MOUSE C_Mouse::GetInstance()