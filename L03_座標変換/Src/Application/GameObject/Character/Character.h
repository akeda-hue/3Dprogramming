#pragma once

class Terrain;

class Character : public KdGameObject
{
public:
	Character() {}
	virtual ~Character()	override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;
	void DrawSprite()		override;

	void SetCamera(std::shared_ptr<KdCamera> _camera) { m_camera = _camera; }

	void SetTerrain(std::shared_ptr<Terrain> _terrain) { m_terrain = _terrain; }

private:
	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;

	std::weak_ptr<Terrain> m_terrain;

	std::weak_ptr<KdCamera> m_camera;

	std::shared_ptr<KdTexture> m_tex;

	Math::Vector3 m_move;

	Math::Vector3 m_targetPos;
};