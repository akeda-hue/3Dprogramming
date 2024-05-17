#pragma once

class Hamster : public KdGameObject
{
public:

	Hamster() {}

	~Hamster() override {}

	void Update();

	void DrawLit();

	void Init();

private:

	//板ポリゴン
	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;

};