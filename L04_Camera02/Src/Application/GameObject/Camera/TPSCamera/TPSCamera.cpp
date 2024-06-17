#include "TPSCamera.h"

void TPSCamera::Update()
{
	//ターゲットの行列
	Math::Matrix targetMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject> spTarget = m_target.lock();
	if (spTarget)
	{
		targetMat = Math::Matrix::CreateTranslation(spTarget->GetPos());
	}

	//カメラの回転
	UpdateRotateByMouse();

	m_mRotation = GetRotationMatrix();

	m_mWorld = m_mLocalPos * m_mRotation * targetMat;

	Camera::Update();
}

void TPSCamera::Init()
{
	//基準点(ターゲット)からどれだけ離れているか
	m_mLocalPos = Math::Matrix::CreateTranslation(0.0f, 3.0f, -10.0f);

	//画面中央
	m_FixMousePos.x = 640;
	m_FixMousePos.y = 320;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	Camera::Init();
}
