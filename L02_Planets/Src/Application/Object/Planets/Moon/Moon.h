#pragma once

#include "../Planets.h"

class Moon : public Planets
{
public:

	Moon() {}

	~Moon()override {}

	void Update() override;

	void Init() override;

	void SetEarthTransMat(Math::Matrix _earthMat) { m_earthMat = _earthMat; }

private:

	Math::Matrix m_earthMat;

};