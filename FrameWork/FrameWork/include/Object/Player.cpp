#include "Player.h"
#include "../Core/Input.h"
#include "Bullet.h"
#include "../Collider/ColliderRect.h"
#include "../Core/Camera.h"
#include "../Animation/Animation.h"

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
	SetSize(73.f, 76.f);
	SetImageOffset(6.f, 0.f);
	SetSpeed(400.f);
	SetPivot(0.5f, 0.5f);
	SetTexture("Player", L"HOS.bmp");

	SetColorKey(249, 0, 249);

	CColliderRect* pRC = AddCollider<CColliderRect>("PlayerBody");

	pRC->SetRect(-30.5f, -38.f, 30.5f, 38.f);
	pRC->AddCollisionFunction(CS_ENTER, this, &CPlayer::Hit);
	pRC->AddCollisionFunction(CS_STAY, this, &CPlayer::HitStay);

	SAFE_RELEASE(pRC);

	m_iHP = 1000;

	//중력을 적용한다.
	SetPhysics(true);

	//점프할 힘을 설정한다.
	SetForce(250.f);

	CAnimation* pAni = CreateAnimation("PlayerAnimation");

	AddAnimationClip("IdleRight", AT_ATLAS, AO_LOOP, 1.f, 6, 1, 0, 0, 6, 1, 0.f, "PlayerIdleRight", L"Player/Idle/Right/Player_Stand_Right.bmp");
	SetAnimationClipColorKey("IdleRight", 249, 0, 249);

	AddAnimationClip("RunRight", AT_ATLAS, AO_ONCE_RETURN, 1.f, 6, 1, 0, 0, 6, 1, 0.f, "PlayerRunRight", L"Player/Run/Right/Player_Run_Right.bmp");
	SetAnimationClipColorKey("RunRight", 249, 0, 249);

	AddAnimationClip("RunLeft", AT_ATLAS, AO_ONCE_RETURN, 1.f, 6, 1, 0, 0, 6, 1, 0.f, "PlayerRunLeft", L"Player/Run/Left/Player_Run_Left.bmp");
	SetAnimationClipColorKey("RunLeft", 249, 0, 249);


	SAFE_RELEASE(pAni);

	return true;
}

void CPlayer::Input(float fDeltaTime)
{
	CMoveObj::Input(fDeltaTime);

	if (KEYPRESS("MoveFront"))
	{
		Jump();
		//MoveYFromSpeed(fDeltaTime, MD_BACK);
	}

	if (KEYPRESS("MoveBack"))
	{
		//MoveYFromSpeed(fDeltaTime, MD_FRONT);
	}

	if (KEYPRESS("MoveLeft"))
	{
		MoveXFromSpeed(fDeltaTime, MD_BACK);
		m_pAnimation->ChangeClip("RunLeft");
	}

	if (KEYPRESS("MoveRight"))
	{
		MoveXFromSpeed(fDeltaTime, MD_FRONT);
		m_pAnimation->ChangeClip("RunRight");
	}

	if (KEYDOWN("Fire"))
	{
		Fire();
	}

	if (KEYDOWN("Skill1"))
	{
		MessageBox(NULL, L"Skill1", L"Skill1", MB_OK);
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
	
	//wchar_t strHP[32] = {};
	//wsprintf(strHP, L"HP : %d", m_iHP);
	//
	//POSITION tPos = m_tPos - m_tSize * m_tPivot;
	//
	//tPos -= GET_SINGLE(CCamera)->GetPos();
	//TextOut(hDC, tPos.x, tPos.y, strHP, lstrlen(strHP)); 
}

CPlayer * CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::Hit(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
{
	if (pDest->GetObj()->GetTag() == "MinionBullet")
	{
		m_iHP -= 100;
	}
	else if (pDest->GetTag() == "StageColl")
	{
		ClearGravity();
		JumpEnd();
		m_tPos.y = pSrc->GetHitPoint().y - m_tPivot.y * m_tSize.y;
	}
}

void CPlayer::HitStay(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
{
	if (pDest->GetTag() == "StageColl")
	{
		ClearGravity();
		JumpEnd();
		m_tPos.y = pSrc->GetHitPoint().y - m_tPivot.y * m_tSize.y;
	}
}

void CPlayer::Fire()
{
	CObj* pBullet = CObj::CreateCloneObj("Bullet", "PlayerBullet", m_pLayer);
	
	pBullet->AddCollisionFunction("BulletBody", CS_ENTER, (CBullet*)pBullet, &CBullet::Hit);

	//Pivot를 이용하여 총알 위치 재조정(가운데)
	POSITION tPos;

	tPos.x = GetRight() + pBullet->GetSize().x * pBullet->GetPivot().x;
	tPos.y = GetCenter().y;

	pBullet->SetPos(tPos);

	SAFE_RELEASE(pBullet);
}
