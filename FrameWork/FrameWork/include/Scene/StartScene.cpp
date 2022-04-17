#include "StartScene.h"
#include "../Object/UIPanel.h"
#include "../Object/UIButton.h"
#include "Layer.h"
#include "../Core/Camera.h"
#include "../Collider/ColliderRect.h"
#include "../Core.h"
#include "SceneManager.h"
#include "InGameScene.h"

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

	pStartBtn->SetPos(GETRESOLUTION.iW / 2 - 100, GETRESOLUTION.iH / 2 - 170);
	pStartBtn->SetSize(200, 100);
	pStartBtn->SetTexture("StartButton", L"StartButton.bmp");

	CColliderRect* pRC = (CColliderRect*)pStartBtn->GetCollider("ButtonBody");

	POSITION tPos = pStartBtn->GetPosition();
	pRC->SetRect(0.f, 0.f, pStartBtn->GetSize().x, pStartBtn->GetSize().y);

	SAFE_RELEASE(pRC);

	pStartBtn->SetCallBack(this, &CStartScene::StartButtonCallBack);
	
	SAFE_RELEASE(pStartBtn);

	CUIButton* pEditButton = CObj::CreateObj<CUIButton>("EditButton", pLayer);

	pEditButton->SetPos(GETRESOLUTION.iW / 2 - 100, GETRESOLUTION.iH / 2 - 50);
	pEditButton->SetSize(200, 100);
	pEditButton->SetTexture("EditButton", L"StartButton.bmp");

	pRC = (CColliderRect*)pEditButton->GetCollider("ButtonBody");

	tPos = pEditButton->GetPosition();
	pRC->SetRect(0.f, 0.f, pEditButton->GetSize().x, pEditButton->GetSize().y);

	SAFE_RELEASE(pRC);

	pEditButton->SetCallBack(this, &CStartScene::StartButtonCallBack);

	SAFE_RELEASE(pEditButton);


	CUIButton* pEndBtn = CObj::CreateObj<CUIButton>("EndButton", pLayer);

	pEndBtn->SetPos(GETRESOLUTION.iW / 2 - 100, GETRESOLUTION.iH / 2 + 70);
	pEndBtn->SetSize(200, 100);
	pEndBtn->SetTexture("EndButton", L"EndButton.bmp");

	pRC = (CColliderRect*)pEndBtn->GetCollider("ButtonBody");

	tPos = pEndBtn->GetPosition();
	pRC->SetRect(0.f, 0.f, pEndBtn->GetSize().x, pEndBtn->GetSize().y);

	SAFE_RELEASE(pRC);

	pEndBtn->SetCallBack(this, &CStartScene::EndButtonCallBack);

	SAFE_RELEASE(pEndBtn);
	
	return true;
}

void CStartScene::StartButtonCallBack(float fTime)
{
	GET_SINGLE(CSceneManager)->CreateScene<CInGameScene>(SC_NEXT);
}

void CStartScene::EndButtonCallBack(float fTime)
{
	GET_SINGLE(CCore)->DestroyGame();
}
