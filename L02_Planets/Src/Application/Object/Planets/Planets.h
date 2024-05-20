#pragma once

class Planets : public KdGameObject
{
public:

	Planets() {}

	virtual ~Planets()override {}

	virtual void Update() override;

	virtual void DrawLit() override;

	virtual void Init() override;

protected:


	std::shared_ptr<KdModelData> m_spModel = nullptr;

private:


};