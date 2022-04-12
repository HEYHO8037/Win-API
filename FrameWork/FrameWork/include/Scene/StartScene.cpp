#include "StartScene.h"
#include "../Object/UIPanel.h"
#include "../Object/UIButton.h"
#include "Layer.h"
#include "../Core/Camera.h"
#include "../Collider/ColliderRect.h"
#include "../Core.h"

CStartScene::CStartScene()
{
}


CStartScene::~CStartScene()
{
}

bool CStartScene::Init()
{
	//부모 클래스의 초기화 함수를 호출해준다.
	if (!CScene::Init())
	{
		return false;
	}

	CLayer* pLayer = FindLayer("UI");

	CUIPanel* pBackPanel = CObj::CreateObj<CUIPanel>("BackPanel", pLayer);

	pBackPanel->SetSize(GETRESOLUTION.iW, GETRESOLUTION.iH);
	pBackPanel->SetTexture("StartBack", L"StartBack.bmp");

	SAFE_RELEASE(pBackPanel);

	CUIButton* pStartBtn = CObj::CreateObj<CUIButton>("StartButton", pLayer);

	pStartBtn->SetPos(GETRESOLUTION.iW / 2 - 100, GETRESOLUTION.iH / 2 - 150);
	pStartBtn->SetSize(200, 100);
	pStartBtn->SetTexture("StartButton", L"StartButton.bmp");

	CColliderRect* pRC = (CColliderRect*)pStartBtn->GetCollider("ButtonBody");

	POSITION tPos = pStartBtn->GetPosition();
	pRC->SetRect(tPos.x, tPos.y, tPos.x + pStartBtn->GetSize().x, tPos.y + pStartBtn->GetSize().y);
	
	SAFE_RELEASE(pRC);
	SAFE_RELEASE(pStartBtn);

	CUIButton* pEndBtn = CObj::CreateObj<CUIButton>("EndButton", pLayer);

	pEndBtn->SetPos(GETRESOLUTION.iW / 2 - 100, GETRESOLUTION.iH / 2 + 50);
	pEndBtn->SetSize(200, 100);
	pEndBtn->SetTexture("EndButton", L"EndButton.bmp");

	pRC = (CColliderRect*)pEndBtn->GetCollider("ButtonBody");

	tPos = pEndBtn->GetPosition();
	pRC->SetRect(tPos.x, tPos.y, tPos.x + pEndBtn->GetSize().x, tPos.y + pEndBtn->GetSize().y);

	SAFE_RELEASE(pRC);
	SAFE_RELEASE(pEndBtn);
	


	return true;
}
