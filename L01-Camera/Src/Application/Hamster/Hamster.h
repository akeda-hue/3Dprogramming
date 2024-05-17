#pragma once

class Hamster : public KdGameObject
{
public:

	Hamster() {}

	~Hamster() override {}

	void Update() override;

	void DrawLit() override;

	void Init() override;

private:

	//板ポリゴン
	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;

};