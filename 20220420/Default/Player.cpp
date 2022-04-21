#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"

CPlayer::CPlayer()
	: m_fAngle(0.f)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 450.f;

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_fSpeed = 5.f;
}

void CPlayer::Update(void)
{
	// 연산을 진행
	Key_Input();



	// 모든 연산이 끝난 뒤에 최종적인 좌표를 완성
	Update_Rect();
}

void CPlayer::Late_Update(void)
{

}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, NULL);

	// X 좌표 + 길이 * sin(라디안 * 앵글)(0~1의 값을 배출함)
	LineTo(hDC, m_tInfo.fX + (m_tInfo.fCX * sinf(RADIAN * m_fAngle)), m_tInfo.fY + (m_tInfo.fCY * cosf(RADIAN * m_fAngle)));

}

void CPlayer::Release(void)
{
	m_pBulletList = nullptr;
}

void CPlayer::SetBulletList(list<CBullet*>* list)
{
	m_pBulletList = list;
}

void CPlayer::Key_Input(void)
{
	// GetKeyState
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_fAngle += m_fSpeed;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_fAngle -= m_fSpeed;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_tInfo.fX += sinf(RADIAN * m_fAngle) * m_fSpeed;
		m_tInfo.fY += cosf(RADIAN * m_fAngle) * m_fSpeed;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_tInfo.fX -= sinf(RADIAN * m_fAngle) * m_fSpeed;
		m_tInfo.fY -= cosf(RADIAN * m_fAngle) * m_fSpeed;
	}
}
