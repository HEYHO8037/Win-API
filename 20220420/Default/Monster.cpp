#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
	: m_bIsLeft(false)
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 150.f;

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_fSpeed = 5.f;
}

void CMonster::Update(void)
{
	CheckCollision();

	if (m_bIsLeft)
	{
		MoveLeft();
	}
	else
	{
		MoveRight();
	}

	Update_Rect();
}

void CMonster::Late_Update(void)
{
}

void CMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release(void)
{
}

RECT CMonster::GetRect() const
{
	return m_tRect;
}

void CMonster::MoveLeft()
{
	m_tInfo.fX -= m_fSpeed;
}

void CMonster::MoveRight()
{
	m_tInfo.fX += m_fSpeed;
}

void CMonster::CheckCollision()
{
	if (m_tRect.left <= 100)
	{
		m_bIsLeft = false;
	}
	if (m_tRect.right >= WINCX - 100)
	{
		m_bIsLeft = true;
	}
}
