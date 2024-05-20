#include "Moon.h"

void Moon::Update()
{
	static float rotatoAngle = 0;
	Math::Matrix rotationMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(rotatoAngle));

	static float revolutionAngle = 0;
	Math::Matrix revolutionMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(revolutionAngle));

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(3, 0, 0);
	m_mWorld = rotationMat * transMat * revolutionMat * m_earthMat;

	rotatoAngle += 1.0f;
	revolutionAngle += 5.0f;
}

void Moon::Init()
{
	m_spModel = std::make_shared<KdModelData>();

	m_spModel->Load("Asset/Data/LessonData/Planets/moon.gltf");
}
