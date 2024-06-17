#pragma once

#include "../Camera.h"

class Player;

class TPSCamera : public Camera
{
public:

	TPSCamera() {}
	~TPSCamera() {}

	void Update() override;

	void Init() override;

private:



};