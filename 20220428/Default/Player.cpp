#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "Shield.h"
#include "ScrewBullet.h"
#include "GuideBullet.h"
#include "ObjMgr.h"
#include "LineMgr.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 100.f;
	m_tInfo.fY = 300.f;

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_fSpeed = 10.f;
	m_fForce = 10.f;

	m_fDiagonal = 100.f;
	m_bIsParabolaJump = false;
	m_bIsNormalJump = false;
	QueryPerformanceFrequency(&timer);
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	// 연산을 진행
	Key_Input();

	if (m_bIsNormalJump)
	{
		m_tInfo.fY -= m_fForce;
	}


	ParabolaPhysics();
	//JumpPhysics();


	// 모든 연산이 끝난 뒤에 최종적인 좌표를 완성
	Update_Rect();

	if (m_tInfo.fY + (m_tInfo.fCY / 2.f) > WINCY)
	{
		m_tInfo.fY = WINCY - (m_tInfo.fCY / 2.f);
		m_bIsNormalJump = false;
		m_bIsParabolaJump = false;
		m_fForce = 10.f;
	}

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	m_tPosin.x = long(m_tInfo.fX + m_fDiagonal * cosf((m_fAngle * PI) / 180.f));
	m_tPosin.y = long(m_tInfo.fY - m_fDiagonal * sinf((m_fAngle * PI) / 180.f));
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	// 포신 그리기
	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	LineTo(hDC, (int)m_tPosin.x, (int)m_tPosin.y);
}

void CPlayer::Release(void)
{
	
}

void CPlayer::Key_Input(void)
{
	float	fY = 0.f;

	// GetKeyState
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;

		//if (CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY))
		//	m_tInfo.fY = fY;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;

		//if (CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY))
		//	m_tInfo.fY = fY;
	}


	if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;

	if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;

	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		if (m_bIsNormalJump || m_bIsParabolaJump)
		{
			return;
		}

		//NormalJump();
		ParabolaJump();
		QueryPerformanceCounter(&start);
	}

	if (GetAsyncKeyState('A'))
		m_fAngle++;

	if (GetAsyncKeyState('D'))
		m_fAngle--;


	/*if (GetAsyncKeyState('W'))
		m_pBullet->push_back(Create_Bullet(DIR_UP));

	if (GetAsyncKeyState('A'))
		m_pBullet->push_back(Create_Bullet(DIR_LEFT));

	if (GetAsyncKeyState('S'))
		m_pBullet->push_back(Create_Bullet(DIR_DOWN));

	if (GetAsyncKeyState('D'))
		m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHT));*/


	/*if (GetAsyncKeyState(VK_LEFT))
	{
		if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}

		else
			m_tInfo.fX -= m_fSpeed;
	}
	
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}

		else
			m_tInfo.fX += m_fSpeed;
	}
		
	else if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;

	else if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;*/

	/*if (GetAsyncKeyState(VK_LEFT))
		m_fAngle -= 5.f;

	if (GetAsyncKeyState(VK_RIGHT))
		m_fAngle += 5.f;
	
	if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fX += m_fSpeed * cosf((m_fAngle * PI) / 180.f);
		m_tInfo.fY -= m_fSpeed * sinf((m_fAngle * PI) / 180.f);
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fX += -m_fSpeed * cosf((m_fAngle * PI) / 180.f);
		m_tInfo.fY -= -m_fSpeed * sinf((m_fAngle * PI) / 180.f);
	}

	if (GetAsyncKeyState(VK_SPACE))
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CGuideBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle));*/


}

template<typename T>
CObj* CPlayer::Create_Bullet(void)
{
	CObj*		pBullet = CAbstractFactory<T>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle);

	return pBullet;
}

CObj* CPlayer::Create_Shield(void)
{
	CObj*		pShield = CAbstractFactory<CShield>::Create();
	pShield->Set_Target(this);

	return pShield;
}

void CPlayer::NormalJump()
{
	if (m_bIsNormalJump)
	{
		return;
	}

	m_bIsNormalJump = true;
}

void CPlayer::ParabolaJump()
{
	if (sinf(m_fAngle * PI / 180) < 0)
	{
		m_bIsParabolaJump = false;
		return;
	}

	m_bIsParabolaJump = true;
}

void CPlayer::ParabolaPhysics()
{
	// Y -= 속도 * sin(각도) * 시간 - 1/2(중력계수(9.8) * 시간 * 시간)
	// X += cos(각도)

	if (!m_bIsParabolaJump)
	{
		return;
	}

	QueryPerformanceCounter(&end);

	m_fDeltaTime = (end.QuadPart - start.QuadPart) / (float)timer.QuadPart;
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180) * m_fDeltaTime - (9.8 * 0.5) * m_fDeltaTime * m_fDeltaTime;
	m_tInfo.fX += cosf(m_fAngle * PI / 180);
}



void CPlayer::JumpPhysics()
{
	if (!m_bIsNormalJump)
	{
		return;
	}

	QueryPerformanceCounter(&end);

	m_fDeltaTime = (end.QuadPart - start.QuadPart) / (float)timer.QuadPart;
	
	m_fForce -= 0.98 * m_fDeltaTime;
}

