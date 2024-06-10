#include "Character.h"
#include "../../main.h"
#include "../Terrain/Terrain.h"
#include "../../Mouse/MouseC.h"

void Character::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}

	m_tex = std::make_shared<KdTexture>();
	m_tex->Load("Asset/Textures/bars.png");
}

void Character::Update()
{
	// キャラクターの移動速度(真似しちゃダメですよ)
	float moveSpd = 0.05f;
	Math::Vector3 nowPos = m_mWorld.Translation();

	//マウスのクリックした所に移動する処理
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		KdCollider::RayInfo ray;
		ray.m_dir = Math::Vector3::Zero;
		ray.m_type = KdCollider::TypeGround;
		std::list<KdCollider::CollisionResult> retRayList;

		m_camera.lock()->GenerateRayInfoFromClientPos(MOUSE.GetMousePos(), ray.m_pos, ray.m_dir, ray.m_range);

		m_terrain.lock()->Intersects(ray, &retRayList);

		for (auto& ret : retRayList)
		{
			m_move = ret.m_hitPos - nowPos;
			m_targetPos = ret.m_hitPos;
		}
	}


	//所定の場所に近づいた場合moveを0にする(めっちゃちっちゃい円判定)
	float radius = 0.05f;
	Math::Vector3 v = m_targetPos - nowPos;

	if (v.Length()<=radius)
	{
		m_move = Math::Vector3::Zero;
		m_targetPos = Math::Vector3::Zero;
	}

	//これで止まるらしいんだけど・・・
	//if (m_move.Length() < moveSpd)moveSpd = m_move.Length();

	m_move.Normalize();
	m_move *= moveSpd;
	nowPos += m_move;

	// キャラクターのワールド行列を創る処理
	m_mWorld = Math::Matrix::CreateTranslation(nowPos);
}

void Character::DrawLit()
{
	if (!m_spPoly) return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Character::DrawSprite()
{
	//↓この赤い点が常にハムスターの原点(足元)に追従するように

	//①ハムスターの3D座標を2D座標に変換する
	Math::Vector3 nowPos = m_mWorld.Translation();
	Math::Vector3 retPos = {};

	if (!m_camera.expired())
	{
		m_camera.lock()->ConvertWorldToScreenDetail(nowPos+Math::Vector3(0.0f,1.5f,0.0f), retPos);
	}

	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, retPos.x, retPos.y, 270, 50);

	

}
