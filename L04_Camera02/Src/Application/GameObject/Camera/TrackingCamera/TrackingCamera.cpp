#include "TrackingCamera.h"

void TrackingCamera::Update()
{
	//ターゲットの行列
	Math::Matrix targetMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject> spTarget = m_target.lock();
	if (spTarget)
	{
		targetMat = Math::Matrix::CreateTranslation(spTarget->GetPos());
	}

	m_mWorld = m_mRotation * m_mLocalPos * targetMat;

	Camera::Update();
}

void TrackingCamera::Init()
{
	//基準点(ターゲット)からどれだけ離れているか
	m_mLocalPos = Math::Matrix::CreateTranslation(0.0f,6.0f,-5.0f);

	//どれだけ傾いているか
	m_mRotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));

	Camera::Init();
}
