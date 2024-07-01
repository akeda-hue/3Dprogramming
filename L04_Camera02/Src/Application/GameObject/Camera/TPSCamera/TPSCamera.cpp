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

	//=================================
	//めり込み防止のための座標補正計算
	//=================================
	//①当たり判定(例判定用の情報作成)
	KdCollider::RayInfo rayInfo;
	rayInfo.m_pos = GetPos();
	rayInfo.m_dir = Math::Vector3::Down;//初期化をしているだけ
	rayInfo.m_range = 1000.0f;
	rayInfo.m_type = KdCollider::TypeGround;

	if (spTarget)
	{
		Math::Vector3 targetPos = spTarget->GetPos() + Math::Vector3(0, 0.1f, 0);
		rayInfo.m_dir = targetPos - GetPos();
		rayInfo.m_range = rayInfo.m_dir.Length();
		rayInfo.m_dir.Normalize();
	}

	//②HIT対象のオブジェクトに総当たり
	for (auto& object : m_hitObjectList)
	{
		std::list<KdCollider::CollisionResult> resultList;
		if (!object.expired())
		{
			object.lock()->Intersects(rayInfo, &resultList);
		}

		//③結果を使って座標を補完する
		float maxOverLap = 0;
		Math::Vector3 hitPos = {};
		bool hit = false;
		for (auto& result : resultList)
		{
			//レイを遮断し、オーバーした長さが一番長いものを探す
			if (maxOverLap < result.m_overlapDistance)
			{
				maxOverLap = result.m_overlapDistance;
				hitPos = result.m_hitPos;
				hit = true;
			}
		}
		if (hit)
		{
			Math::Vector3 hoseiPos = hitPos;
			hoseiPos += rayInfo.m_dir * 0.4f;

			SetPos(hoseiPos);
		}
	}

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
