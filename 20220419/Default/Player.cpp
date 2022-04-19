#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_fSpeed = 10.f;
}

void CPlayer::Update(void)
{
	// 연산을 진행
	Key_Input();



	// 모든 연산이 끝난 뒤에 최종적인 좌표를 완성
	Update_Rect();
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release(void)
{
	m_pBulletList = nullptr;
}

void CPlayer::GetBulletList(list<CBullet*>* list)
{
	m_pBulletList = list;
}

void CPlayer::Key_Input(void)
{
	// GetKeyState
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		CBullet* pBullet = new CBullet(m_tInfo, LEFT);
		m_pBulletList->push_back(pBullet);
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		CBullet* pBullet = new CBullet(m_tInfo, RIGHT);
		m_pBulletList->push_back(pBullet);
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		CBullet* pBullet = new CBullet(m_tInfo, UP);
		m_pBulletList->push_back(pBullet);
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		CBullet* pBullet = new CBullet(m_tInfo, DOWN);
		m_pBulletList->push_back(pBullet);
	}
}
