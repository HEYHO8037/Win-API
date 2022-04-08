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
	SetSize(76.f, 76.f);
	SetSpeed(400.f);
	SetPivot(0.5f, 0.5f);
	SetTexture("Player", L"HOS.bmp");

	SetColorKey(248, 0, 248);

	CColliderRect* pRC = AddCollider<CColliderRect>("PlayerBody");

	pRC->SetRect(-38.f, -38.f, 38.f, 38.f);
	pRC->AddCollisionFunction(CS_ENTER, this, &CPlayer::Hit);
	pRC->AddCollisionFunction(CS_STAY, this, &CPlayer::HitStay);

	SAFE_RELEASE(pRC);

	m_iHP = 1000;

	//�߷��� �����Ѵ�.
	SetPhysics(true);

	//������ ���� �����Ѵ�.
	SetForce(250.f);

	CAnimation* pAni = CreateAnimation("PlayerAnimation");

	AddAnimationClip("IdleRight", AT_ATLAS, AO_LOOP, 1.f, 6, 1, 0, 0, 6, 1, 0.f, "PlayerIdleRight", L"Player/Idle/Right/Player_Stand_Right.bmp");
	SetAnimationClipColorKey("IdleRight", 248, 0, 248);


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
	}

	if (KEYPRESS("MoveRight"))
	{
		MoveXFromSpeed(fDeltaTime, MD_FRONT);
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
	
	wchar_t strHP[32] = {};
	wsprintf(strHP, L"HP : %d", m_iHP);
	
	POSITION tPos = m_tPos - m_tSize * m_tPivot;
	
	tPos -= GET_SINGLE(CCamera)->GetPos();
	TextOut(hDC, tPos.x, tPos.y, strHP, lstrlen(strHP)); 
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

	//Pivot�� �̿��Ͽ� �Ѿ� ��ġ ������(���)
	POSITION tPos;

	tPos.x = GetRight() + pBullet->GetSize().x * pBullet->GetPivot().x;
	tPos.y = GetCenter().y;

	pBullet->SetPos(tPos);

	SAFE_RELEASE(pBullet);
}
