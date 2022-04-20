#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}

CBullet::CBullet(INFO& info, eDir dir)
{
	m_tInfo.fX = info.fX;
	m_tInfo.fY = info.fY;
	m_tInfo.fCX = info.fCX;
	m_tInfo.fCY = info.fCY;
	m_fSpeed = 10;

	m_eDir = dir;
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize(void)
{
}

void CBullet::Update(void)
{
	if (m_eDir == UP)
	{
		m_tInfo.fY -= m_fSpeed;
	}
	else if (m_eDir == DOWN)
	{
		m_tInfo.fY += m_fSpeed;
	}
	else if (m_eDir == LEFT)
	{
		m_tInfo.fX -= m_fSpeed;
	}
	else
	{
		m_tInfo.fX += m_fSpeed;
	}

	Update_Rect();
}

void CBullet::Late_Update(void)
{

}

void CBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release(void)
{
}

RECT CBullet::GetRect() const
{
	return m_tRect;
}

