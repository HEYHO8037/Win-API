#include "InGameScene.h"
#include "../Object/Player.h"
#include "Layer.h"



CInGameScene::CInGameScene()
{
}


CInGameScene::~CInGameScene()
{
}

bool CInGameScene::Init()
{
	//�θ� Scene Ŭ������ �ʱ�ȭ �Լ��� ȣ�����ش�.
	if (!CScene::Init())
	{
		return false;
	}

	CLayer* pLayer = FindLayer("Default");

	CPlayer* pPlayer = CObj::CreateObj<CPlayer>("Player", pLayer);

	SAFE_RELEASE(pPlayer);

	return true;
}
