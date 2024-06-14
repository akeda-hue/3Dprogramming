#pragma once

#include "../Camera.h"

class Player;

class FPSCamera : public Camera
{
public:

	FPSCamera() {}
	~FPSCamera() {}

	void Update() override;

	void Init() override;

private:

	

};