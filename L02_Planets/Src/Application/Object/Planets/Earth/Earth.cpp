#include "Earth.h"
#include "../Moon/Moon.h"

void Earth::Update()
{
	static float rotatoAngle = 0;
	Math::Matrix rotationMat=Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(rotatoAngle));

	static float revolutionAngle = 0;
	Math::Matrix revolutionMat= Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(revolutionAngle));

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(5,0,0);
	m_mWorld = rotationMat * transMat * revolutionMat;

	rotatoAngle += 1.0f;
	revolutionAngle += 1.0f;

	m_moon->SetEarthTransMat(m_mWorld);

	m_moon->Update();
}

void Earth::DrawLit()
{
	Planets::DrawLit();

	m_moon->DrawLit();
}

void Earth::Init()
{
	m_spModel = std::make_shared<KdModelData>();

	m_spModel->Load("Asset/Data/LessonData/Planets/earth.gltf");

	m_moon = std::make_shared<Moon>();
	m_moon->Init();
}
