#pragma once

#include "../Camera.h"

class Player;

class TrackingCamera : public Camera
{
public:

	TrackingCamera() {}
	~TrackingCamera() {}

	void Update() override;

	void Init() override;

private:



};