#include "Hamster.h"

void Hamster::Update()
{
	//ベクトル
	//キャラクターの動速度
	float moveSpd = 0.05f;
	Math::Vector3 m_nowPos = m_mWorld.Translation();

	//移動したい「方向ベクトル」=絶対に長さが「1」でなければならない
	Math::Vector3 moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('W') & 0x8000)
	{
		moveVec.z = 1.0f;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		moveVec.x = -1.0f;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		moveVec.z = -1.0f;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		moveVec.x = 1.0f;
	}

	//正規化・・・合成ベクトルの長さを1にする
	moveVec.Normalize();
	moveVec *= moveSpd;

	m_nowPos += moveVec;

	m_mWorld = Math::Matrix::CreateTranslation(m_nowPos);
}

void Hamster::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Hamster::Init()
{
	m_spPoly = std::make_shared<KdSquarePolygon>();
	m_spPoly->SetMaterial("Asset/Data/LessonData/Character/hamster.png");
	m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
}
