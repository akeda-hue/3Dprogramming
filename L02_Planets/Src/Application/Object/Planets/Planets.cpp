#include "Planets.h"

void Planets::Update()
{
}

void Planets::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Planets::Init()
{
	m_spModel = std::make_shared<KdModelData>();

	m_spModel->Load("Asset/Data/LessonData/Planets/sun.gltf");
}
