#include "CCTVCamera.h"

void CCTVCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 基準点(ターゲット)の目線
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 6.0f, -10.0f);

	//いったん行列を確定させる
	m_mWorld = m_mLocalPos;
}

void CCTVCamera::PostUpdate()
{
	std::shared_ptr<KdGameObject> target = m_wpTarget.lock();
	Math::Matrix targetMat = Math::Matrix::Identity;
	if (target)
	{
		targetMat = Math::Matrix::CreateTranslation(target->GetPos());
	}


	//プレイヤーを角度で追従するように
	UpdateLookAtRotate(targetMat.Translation());
}

void CCTVCamera::UpdateLookAtRotate(const Math::Vector3& _targetPos)
{
	//characterから見たカメラの座標
	Math::Matrix shadowVP = DirectX::XMMatrixLookAtLH(GetPos(), _targetPos, Math::Vector3::Up);

	//逆行列をわたす
	m_mWorld = shadowVP.Invert();
}
