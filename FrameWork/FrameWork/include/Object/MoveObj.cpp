#include "MoveObj.h"



CMoveObj::CMoveObj()
	: m_fAngle(0.f),
	m_fSpeed(100.f),
	m_bMove(false),
	m_bFalling(true),
	m_fForceOrigin(0.f),
	m_fForce(0.f)
{
}

CMoveObj::CMoveObj(const CMoveObj & obj)
	: CObj(obj)
{
	m_fAngle = obj.m_fAngle;
	m_fSpeed = obj.m_fSpeed;
	m_fForceOrigin = obj.m_fForceOrigin;
	m_fForce = 0.f;

	m_bMove = false;
	m_bFalling = false;
}


CMoveObj::~CMoveObj()
{

}

void CMoveObj::SetForce(float fForce)
{
	m_fForceOrigin = fForce;
}

void CMoveObj::SetAngle(float fAngle)
{
	m_fAngle = fAngle;
}

void CMoveObj::SetSpeed(float fSpeed)
{
	m_fSpeed = fSpeed;
}

float CMoveObj::GetAngle() const
{
	return m_fAngle;
}

float CMoveObj::GetSpeed() const
{
	return m_fSpeed;
}

void CMoveObj::Move(float x, float y)
{
	m_tPos.x += x;	
	m_tPos.y += y;

	m_bMove = true;
}

void CMoveObj::Move(float x, float y, float fDeltaTime)
{
	m_tPos.x = x * fDeltaTime;
	m_tPos.y = y * fDeltaTime;

	m_bMove = true;
}

void CMoveObj::Move(const POSITION& tMove)
{
	m_tPos += tMove;

	m_bMove = true;
}

void CMoveObj::Move(const POSITION& tMove, float fDeltaTime)
{
	m_tPos += tMove * fDeltaTime;
	m_bMove = true;
}

void CMoveObj::MoveX(float x)
{
	m_tPos.x += x;
	m_bMove = true;
}

void CMoveObj::MoveX(float x, float fDeltaTime)
{
	m_tPos.x += x * fDeltaTime;
	m_bMove = true;
}

void CMoveObj::MoveXFromSpeed(float fDeltaTime, MOVE_DIR eDir)
{
	m_tPos.x += m_fSpeed * fDeltaTime * eDir;
	m_bMove = true;
}

void CMoveObj::MoveY(float y)
{
	m_tPos.y += y;
	m_bMove = true;
}

void CMoveObj::MoveY(float y, float fDeltaTime)
{
	m_tPos.y += y * fDeltaTime;
	m_bMove = true;
}

void CMoveObj::MoveYFromSpeed(float fDeltaTime, MOVE_DIR eDir)
{
	m_tPos.y += m_fSpeed * fDeltaTime * eDir;
	m_bMove = true;
}

void CMoveObj::MoveAngle()
{
	m_tPos.x += cosf(m_fAngle) * m_fSpeed;
	m_tPos.y += sinf(m_fAngle) * m_fSpeed;
	m_bMove = true;
}

void CMoveObj::MoveAngle(float fTime)
{
	m_tPos.x += cosf(m_fAngle) * m_fSpeed * fTime;
	m_tPos.y += sinf(m_fAngle) * m_fSpeed * fTime;
	m_bMove = true;
}

void CMoveObj::Jump()
{
	if (!m_bFalling)
	{
		m_bFalling = true;
		m_fForce = m_fForceOrigin;
	}
}

void CMoveObj::JumpEnd()
{
	m_bFalling = false;
	m_fForce = 0.f;
}


void CMoveObj::Input(float fDeltaTime)
{
	CObj::Input(fDeltaTime);
}

int CMoveObj::Update(float fDeltaTime)
{
	if (m_bIsPhysics)
	{
		m_fGravityTime += fDeltaTime;

		// ???? ?????? ???? ???? ???? ??????.
		m_fForce -= (GRAVITY * m_fGravityTime * m_fGravityTime);
		m_tPos.y -= m_fForce * fDeltaTime;
	}

	CObj::Update(fDeltaTime);


	return 0;
}

int CMoveObj::LateUpdate(float fDeltaTime)
{
	CObj::LateUpdate(fDeltaTime);
	return 0;
}

void CMoveObj::Collision(float fDeltaTime)
{
	CObj::Collision(fDeltaTime);
}

void CMoveObj::Render(HDC hDC, float fDeltaTime)
{
	CObj::Render(hDC, fDeltaTime);
	m_bMove = false;
}
