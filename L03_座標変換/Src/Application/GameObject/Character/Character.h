﻿#pragma once

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

private:
	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;

	std::weak_ptr<KdCamera> m_camera;

	std::shared_ptr<KdTexture> m_tex;
};