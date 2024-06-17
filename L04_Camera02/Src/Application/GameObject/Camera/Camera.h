#pragma once
#include <tiny_gltf.h>

class Camera : public KdGameObject
{
public:

	Camera() {}
	~Camera()override {}

	void Update() override;

	void PreDraw() override;

	void Init() override;


	//カメラのターゲットとしたいオブジェクトをセットする関数
	void SetTarget(std::shared_ptr<KdGameObject> _target)
	{
		m_target = _target;
	}

	const Math::Matrix GetRotationMatrix()
	{
		return Math::Matrix::CreateFromYawPitchRoll
		(
			DirectX::XMConvertToRadians(m_DegAng.y),
			DirectX::XMConvertToRadians(m_DegAng.x),
			DirectX::XMConvertToRadians(m_DegAng.z)
		);
	}

protected:

	void UpdateRotateByMouse();

	Math::Matrix m_mLocalPos;
	Math::Matrix m_mRotation;

	POINT m_FixMousePos;

	std::shared_ptr<KdCamera> m_camera = nullptr;

	std::weak_ptr<KdGameObject> m_target;

	//カメラ回転用
	Math::Vector3 m_DegAng;

private:



};