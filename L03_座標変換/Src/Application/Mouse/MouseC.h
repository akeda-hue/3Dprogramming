#pragma once

class C_Mouse
{
//�ϐ�
private:
	POINT mousePos;

//�֐�
public:
	void Init();

	POINT GetMousePos();

	bool IsInsideBox(Math::Vector2 a_pos,float a_halfHeight,float a_halfWidth);

	float CalcDeg(Math::Vector2 a_pos);

//�R���X�g���N�^���f�X�g���N�^
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