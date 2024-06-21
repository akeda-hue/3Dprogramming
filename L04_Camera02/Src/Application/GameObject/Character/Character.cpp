#include "Character.h"
#include "../../main.h"

#include "../Camera/Camera.h"

void Character::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}
}

void Character::Update()
{


	// キャラクターの移動速度(真似しちゃダメですよ)
	float moveSpd = 0.05f;
	Math::Vector3 nowPos = m_mWorld.Translation();

	Math::Vector3 moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('D')) { moveVec.x = 1.0f; }
	if (GetAsyncKeyState('A')) { moveVec.x = -1.0f; }
	if (GetAsyncKeyState('W')) { moveVec.z = 1.0f; }
	if (GetAsyncKeyState('S')) { moveVec.z = -1.0f; }

	std::shared_ptr<Camera>_spCamera = m_camera.lock();
	if (_spCamera)
	{
		// 第二引数で指定された角度のベクトルを生成して第一引数に入れている
		moveVec = moveVec.TransformNormal(moveVec, _spCamera->GetRotationYMatrix());
	}

	moveVec.Normalize();
	moveVec *= moveSpd;
	nowPos += moveVec;

	//キャラクターの回転角度を求める
	UpdateRotate(moveVec);


	// キャラクターのワールド行列を創る処理
	Math::Matrix rotation = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_WorldRot.y));

	m_mWorld = rotation * Math::Matrix::CreateTranslation(nowPos);
}

void Character::DrawLit()
{
	if (!m_spPoly) return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Character::UpdateRotate(const Math::Vector3 _moveVec)
{
	//何も入力がない場合は処理しない
	//Lengthはそれなりに重いので毎フレーム実行しないほうが良い
	if (_moveVec.LengthSquared() == 0.0f)return;

	//キャラの正面方向ベクトル
	Math::Vector3 nowDir = GetMatrix().Backward();
	nowDir.Normalize();

	//移動方向ベクトル
	Math::Vector3 targetDir = _moveVec;
	targetDir.Normalize();

	float nowAng = atan2(nowDir.x,nowDir.z);
	nowAng = DirectX::XMConvertToDegrees(nowAng);

	float targetAng = atan2(targetDir.x, targetDir.z);
	targetAng = DirectX::XMConvertToDegrees(targetAng);

	//角度の差分を求める
	float betweenAng = targetAng - nowAng;
	if (betweenAng > 180)
	{
		betweenAng -= 360;
	}
	else if (betweenAng < -180)
	{
		betweenAng += 360;
	}

	float totateAng = std::clamp(betweenAng, -8.0f, 8.0f);
	m_WorldRot.y += totateAng;
}

