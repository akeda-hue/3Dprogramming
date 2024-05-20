#pragma once

#include "../Planets.h"

class Moon;

class Earth : public Planets
{
public:

	Earth() {}

	~Earth()override {}

	void Update() override;

	void DrawLit() override;

	void Init() override;

private:

	std::shared_ptr<Moon> m_moon = nullptr;

};