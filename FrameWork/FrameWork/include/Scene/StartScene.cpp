#include "StartScene.h"
#include "../Object/UIPanel.h"
#include "Layer.h"
#include "../Core/Camera.h"
#include "../Collider/ColliderPixel.h"
#include "../Core.h"

CStartScene::CStartScene()
{
}


CStartScene::~CStartScene()
{
}

bool CStartScene::Init()
{
	//�θ� Ŭ������ �ʱ�ȭ �Լ��� ȣ�����ش�.
	if (!CScene::Init())
	{
		return false;
	}

	CLayer* pLayer = FindLayer("UI");

	CUIPanel* pBackPanel = CObj::CreateObj<CUIPanel>("BackPanel", pLayer);

	pBackPanel->SetSize(GETRESOLUTION.iW, GETRESOLUTION.iH);
	pBackPanel->SetTexture("StartBack", L"StartBack.bmp");

	SAFE_RELEASE(pBackPanel);


	return true;
}
