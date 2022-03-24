#include "Player.h"



CPlayer::CPlayer()
{
}

CPlayer::CPlayer(const CPlayer & player)
	: CMoveObj(player)
{
}


CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
	SetPos(50.f, 50.f);
	SetSize(100.f, 100.f);
	SetSpeed(400.f);
	SetPivot(0.5f, 0.5f);
	SetTexture("Player", L"HOS.bmp");

	return true;
}

void CPlayer::Input(float fDeltaTime)
{
	CMoveObj::Input(fDeltaTime);

	if (GetAsyncKeyState('W') & 0x8000)
	{
		MoveYFromSpeed(fDeltaTime, MD_BACK);
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		MoveYFromSpeed(fDeltaTime, MD_FRONT);
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		MoveXFromSpeed(fDeltaTime, MD_BACK);
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		MoveXFromSpeed(fDeltaTime, MD_FRONT);
	}

	if (GetAsyncKeyState(VK_SPACE) & 0X8000)
	{
		Fire();
	}
}

int CPlayer::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);
	return 0;
}

int CPlayer::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CPlayer::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

void CPlayer::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC, fDeltaTime);
}

CPlayer * CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::Fire()
{
	CObj* pBullet = CObj::CreateCloneObj("Bullet", "PlayerBullet", m_pLayer);
	

	//Pivot를 이용하여 총알 위치 재조정(가운데)
	POSITION tPos;

	tPos.x = GetRight() + pBullet->GetSize().x * pBullet->GetPivot().x;
	tPos.y = GetCenter().y;

	pBullet->SetPos(tPos);

	SAFE_RELEASE(pBullet);
}
