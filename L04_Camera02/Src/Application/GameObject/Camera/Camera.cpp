#include "Camera.h"

void Camera::Update()
{
	if (!m_camera)return;

	m_camera->SetCameraMatrix(m_mWorld);
}

void Camera::PreDraw()
{
	if (!m_camera)return;

	m_camera->SetToShader();
}

void Camera::Init()
{
	if (!m_camera)
	{
		m_camera = std::make_shared<KdCamera>();
	}
}

void Camera::UpdateRotateByMouse()
{
	POINT nowPos;
	GetCursorPos(&nowPos);

	POINT mouseMove{};
	mouseMove.x = nowPos.x - m_FixMousePos.x;
	mouseMove.y = nowPos.y - m_FixMousePos.y;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	//上の差分をもとに再度画面中央へ固定
	//0.15:マウス感度
	m_DegAng.x += mouseMove.y * 0.15;
	m_DegAng.y += mouseMove.x * 0.15;
}
