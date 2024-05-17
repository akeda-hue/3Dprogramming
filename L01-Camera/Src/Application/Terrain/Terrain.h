#pragma once

class Terrain : public KdGameObject
{
public:

	Terrain() {}

	~Terrain() override {}

	void Update() override;

	void DrawLit() override;

	void Init() override;

private:


	std::shared_ptr<KdModelData> m_spModel = nullptr;

};