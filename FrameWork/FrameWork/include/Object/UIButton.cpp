#include "UIButton.h"
#include "../Collider/ColliderRect.h"
#include "../Core/Input.h"


CUIButton::CUIButton()
	: m_bEnableCallBack(false),
	  m_eState(BS_NONE)
{
}

CUIButton::CUIButton(const CUIButton & button)
	: CUI(button)
{
	m_bEnableCallBack = false;
	m_eState = BS_NONE;
}


CUIButton::~CUIButton()
{
}

bool CUIButton::Init()
{
	CColliderRect* pColl = AddCollider<CColliderRect>("ButtonBody");

	pColl->AddCollisionFunction(CS_ENTER, this, &CUIButton::MouseOn);
	pColl->AddCollisionFunction(CS_LEAVE, this, &CUIButton::MouseOut);

	SAFE_RELEASE(pColl);

	return true;
}

void CUIButton::Input(float fDeltaTime)
{
	CUI::Input(fDeltaTime);
}

int CUIButton::Update(float fDeltaTime)
{
	CUI::Update(fDeltaTime);
	return 0;
}

int CUIButton::LateUpdate(float fDeltaTime)
{
	CUI::LateUpdate(fDeltaTime);

	if (m_eState != BS_NONE)
	{
		if (KEYPRESS("MouseLButton"))
		{
			m_eState = BS_CLICK;
		}
	}

	if (m_eState == BS_CLICK && KEYUP("MouseLButton"))
	{
		if (m_bEnableCallBack)
		{
			m_BtnCallBack(fDeltaTime);
		}
	}

	return 0;
}

void CUIButton::Collision(float fDeltaTime)
{
	CUI::Collision(fDeltaTime);
}

void CUIButton::Render(HDC hDC, float fDeltaTime)
{
	CUI::Render(hDC, fDeltaTime);
}

CUIButton * CUIButton::Clone()
{
	return new CUIButton(*this);
}

void CUIButton::MouseOn(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
{
	if (pDest->GetTag() == "Mouse")
	{
		m_eState = BS_MOUSEON;
	}
}

void CUIButton::MouseOut(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
{
	if (pDest->GetTag() == "Mouse")
	{
		m_eState = BS_NONE;
	}
}
