#include "../main.h"
#include "MouseC.h"

void C_Mouse::Init()
{
	mousePos = { 0,0 };
}

POINT C_Mouse::GetMousePos()
{

	POINT mousePos;
	//ディスプレイ上のマウス座標を取得（ディスプレイの左上が（0，0））
	GetCursorPos(&mousePos);

	//指定のウィンドウ基準のマウス座標に変換（ウィンドウの左上が（0，0））
	
	ScreenToClient(Application::Instance().GetWindowHandle(), &mousePos);

	return mousePos;
}

bool C_Mouse::IsInsideBox(Math::Vector2 a_pos, float a_halfHeight, float a_halfWidth)
{
	POINT mousePos = GetMousePos();
	bool insideX = mousePos.x<a_pos.x + a_halfWidth && mousePos.x>a_pos.x - a_halfWidth;
	bool insideY = mousePos.y < a_pos.y + a_halfHeight && mousePos.y>a_pos.y-a_halfHeight;
	if (insideX&&insideY)
	{
		return true;
	}
	return false;
}

float C_Mouse::CalcDeg(Math::Vector2 a_pos)
{
	POINT mousePos = GetMousePos();
	float a = mousePos.x - a_pos.x;
	float b = mousePos.y - a_pos.y;
	return atan2(b,a);
}
