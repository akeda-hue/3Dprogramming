#include "GameScene.h"
#include"../SceneManager.h"

#include "../../GameObject/Terrain/Terrain.h"
#include "../../GameObject/Character/Character.h"

#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Camera/CCTVCamera/CCTVCamera.h"

// 少数第n位で四捨五入する
void round_n(float& number, int n)
{
	number = number * pow(10, n - 1);
	number = round(number);
	number /= pow(10, n - 1);
}

void GameScene::Init()
{
	//===================================================================
	// ステージ初期化
	//===================================================================
	std::shared_ptr<Terrain> _terrain = std::make_shared<Terrain>();
	_terrain->Init();
	AddObject(_terrain);

	//===================================================================
	// キャラクター初期化
	//===================================================================
	std::shared_ptr<Character> _character = std::make_shared<Character>();
	_character->Init();
	AddObject(_character);

	//===================================================================
	// カメラ初期化
	//===================================================================
	//std::shared_ptr<FPSCamera>		_camera = std::make_shared<FPSCamera>();
	//std::shared_ptr<TPSCamera>		_camera = std::make_shared<TPSCamera>();
	std::shared_ptr<CCTVCamera>		_camera = std::make_shared<CCTVCamera>();
	_camera->Init();
	_camera->SetTarget(_character);
	_camera->RegistHitObject(_terrain);
	_character->SetCamera(_camera);
	AddObject(_camera);

	//===================================================================
	// 乱数実験
	//===================================================================
	//int randRes[10] = {};

	////いかにrandが偏るか
	//srand((unsigned)time(NULL));
	//for (int i=0;i<100000000;i++)
	//{
	//	int tmp = rand() % 10000;
	//	int idx = tmp / 1000;

	//	randRes[idx]++;
	//}

	////結果を出力
	//OutputDebugStringA("-----------------------------------------------------\n");
	//for (int i = 0; i < 10; i++)
	//{
	//	std::stringstream ss;
	//	ss << "取得した値が" << i * 1000 << "～" << (i + 1) * 1000 << "の件数 : \t" << randRes[i] << "\n";
	//	std::string str = ss.str();

	//	OutputDebugStringA(str.c_str());
	//}
	//OutputDebugStringA("-----------------------------------------------------\n");


	////============================
	////メルセンヌツイスタ
	////============================
	//for (int i = 0; i < 100000000; i++)
	//{
	//	int tmp = KdGetInt(0, 9999);
	//	int idx = tmp / 1000;

	//	randRes[idx]++;
	//}

	////結果を出力
	//OutputDebugStringA("-----------------------------------------------------\n");
	//for (int i = 0; i < 10; i++)
	//{
	//	std::stringstream ss;
	//	ss << "取得した値が" << i * 1000 << "～" << (i + 1) * 1000 << "の件数 : \t" << randRes[i] << "\n";
	//	std::string str = ss.str();

	//	OutputDebugStringA(str.c_str());
	//}
	//OutputDebugStringA("-----------------------------------------------------\n");


	//レッスンその1:CカードとRカードをそれぞれ50%の確率で起動時に表示せよ
	/*OutputDebugStringA("-----------------------------------------------------\n");
	int i = KdGetInt(0, 1);
	if (i == 0)
	{
		std::stringstream ss;
		ss << "Cカードゲット\n";
		std::string str = ss.str();

		OutputDebugStringA(str.c_str());
	}
	else
	{
		std::stringstream ss;
		ss << "Rカードゲット\n";
		std::string str = ss.str();

		OutputDebugStringA(str.c_str());

	}
	OutputDebugStringA("-----------------------------------------------------\n");*/

	//レッスンその1:CカードとRカードをそれぞれ50%の確率で起動時に表示せよ(試行回数ver)
	/*int thusenNum = 10000000;
	int tousenNum[2] = {};
	for (int i=0;i<thusenNum;i++)
	{
		int rand = KdGetInt(0, 1);
		tousenNum[rand]++;
	}

	OutputDebugStringA("-----------------------------------------------------\n");
	float prob = 0;
	for (int i = 0; i < std::size(tousenNum); i++)
	{
		std::stringstream ss;
		prob = ((float)tousenNum[i] / (float)thusenNum) * 100;
		round_n(prob, 3);
		switch (i)
		{
		case 0:
			ss << "Cカード" << "当選回数=" << tousenNum[0] << "" << "当選確率=" << prob << "%" << "\n";
			break;
		case 1:

			ss << "Rカード" << "当選回数=" << tousenNum[1] << " " << "当選確率=" << prob << "%" << "\n";
			break;
		}
		std::string str = ss.str();
		OutputDebugStringA(str.c_str());
	}
	OutputDebugStringA("-----------------------------------------------------\n");*/



	//レッスンその2:CカードとRカードをそれぞれ99.5%,0.5%の確率で起動時に表示せよ
	//int bunbo = 1000;
	//int thusenNum = 10000000;
	//int tousenNum[2] = {};
	//for (int i = 0; i < thusenNum; i++)
	//{
	//	int rand = KdGetInt(0, bunbo-1);
	//	if (rand < 5)
	//	{
	//		tousenNum[1]++;
	//	}
	//	else
	//	{
	//		tousenNum[0]++;
	//	};
	//}

	//OutputDebugStringA("-----------------------------------------------------\n");
	//float prob = 0;
	//for (int i = 0; i < std::size(tousenNum); i++)
	//{
	//	std::stringstream ss;
	//	prob = ((float)tousenNum[i] / (float)thusenNum) * 100;
	//	round_n(prob, 3);
	//	switch (i)
	//	{
	//	case 0:
	//		ss << "Cカード" << "当選回数=" << tousenNum[0] << " " << "当選確率=" << prob << "%" << "\n";
	//		break;
	//	case 1:
	//		ss << "Rカード" << "当選回数=" << tousenNum[1] << " " << "当選確率=" << prob << "%" << "\n";
	//		break;
	//	}
	//	std::string str = ss.str();
	//	OutputDebugStringA(str.c_str());
	//}
	//OutputDebugStringA("-----------------------------------------------------\n");


	//レッスンその3:CカードとRカードとSRカードをそれぞれ34%,33%,33%の確率で起動時に表示せよ
	//レッスンその3:CカードとRカードとSRカードをそれぞれ50%,49.5%,0.5%の確率で起動時に表示せよ
	int bunbo = 1000;
	int thusenNum = 10000000;
	int randNum[3] = { 500,495,5 };//当選確率(%)
	int tousenNum[3] = {};
	for (int i = 0; i < thusenNum; i++)
	{
		int rand = KdGetInt(0, bunbo - 1);
		for (int j = 0; j < std::size(randNum); j++)
		{
			rand -= randNum[j];
			if (rand < 0)
			{
				tousenNum[j]++;
				break;
			}
		}

	}

	OutputDebugStringA("-----------------------------------------------------\n");
	float prob = 0;
	for (int i = 0; i < std::size(tousenNum); i++)
	{
		std::stringstream ss;
		prob = ((float)tousenNum[i] / (float)thusenNum) * 100;
		round_n(prob, 3);
		switch (i)
		{
		case 0:
			ss << "Cカード" << "当選回数=" << tousenNum[0] << " " << "当選確率=" << prob << "%" << "\n";
			break;
		case 1:
			ss << "Rカード" << "当選回数=" << tousenNum[1] << " " << "当選確率=" << prob << "%" << "\n";
			break;
		case 2:
			ss << "SRカード" << "当選回数=" << tousenNum[2] << " " << "当選確率=" << prob << "%" << "\n";
			break;
		}
		std::string str = ss.str();
		OutputDebugStringA(str.c_str());
	}
	OutputDebugStringA("-----------------------------------------------------\n");
	

}

void GameScene::Event()
{
}