#pragma once

class Camera;

class Character : public KdGameObject
{
public:
	Character() {}
	virtual ~Character()	override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;

	void SetCamera(std::shared_ptr<Camera> _camera) { m_camera = _camera; }

private:

	void UpdateRotate(const Math::Vector3 _moveVec);

	std::weak_ptr<Camera> m_camera;

	std::shared_ptr<KdSquarePolygon>	m_spPoly	= nullptr;

	Math::Vector3 m_WorldRot = {};
};