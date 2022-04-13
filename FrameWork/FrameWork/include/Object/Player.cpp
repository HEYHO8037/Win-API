#include "Player.h"
#include "../Core/Input.h"
#include "Bullet.h"
#include "../Collider/ColliderRect.h"
#include "../Core/Camera.h"
#include "../Animation/Animation.h"
#include "../Scene/Scene.h"

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
	SetSize(73.f, 80.f);
	SetImageOffset(5.5f, 0.f);
	SetSpeed(50.f);
	SetPivot(0.5f, 0.5f);

	//SetTexture("Player", L"HOS.bmp");
	//SetColorKey(249, 0, 249);

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

	AddAnimationClip("IdleLeft", AT_ATLAS, AO_LOOP, 1.f, 6, 1, 0, 0, 6, 1, 0.f, "PlayerIdleLeft", L"Player/Idle/Left/Player_Stand_Left.bmp");
	SetAnimationClipColorKey("IdleLeft", 249, 0, 249);

	AddAnimationClip("RunRight", AT_ATLAS, AO_ONCE_RETURN, 1.f, 6, 1, 0, 0, 6, 1, 0.f, "PlayerRunRight", L"Player/Run/Right/Player_Run_Right.bmp");
	SetAnimationClipColorKey("RunRight", 249, 0, 249);

	AddAnimationClip("RunLeft", AT_ATLAS, AO_ONCE_RETURN, 1.f, 6, 1, 0, 0, 6, 1, 0.f, "PlayerRunLeft", L"Player/Run/Left/Player_Run_Left.bmp");
	SetAnimationClipColorKey("RunLeft", 249, 0, 249);

	AddAnimationClip("NormalAttackRight", AT_ATLAS, AO_ONCE_RETURN, 1.f, 11, 1, 0, 0, 11, 1, 0.f, "PlayerAttackRight", L"Player/NormalAttack/Right/Player_Attack_Right.bmp");
	SetAnimationClipColorKey("NormalAttackRight", 249, 0, 249);

	//AddAnimationClip("NormalAttackLeft", AT_ATLAS, AO_ONCE_RETURN, 1.f, 11, 1, 0, 0, 11, 1, 0.f, "PlayerAttackLeft", L"Player/NormalAttack/Left/Player_Attack_Left.bmp");
	//SetAnimationClipColorKey("NormalAttackLeft", 249, 0, 249);

	vector<wstring> vecFileName;

	for (int i = 8; i <= 18; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Player/NormalAttack/Left/%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip("NormalAttackLeft", AT_FRAME, AO_ONCE_RETURN, 1.f, 11, 1, 0, 0, 11, 1, 0.f, "PlayerAttackLeft", vecFileName);
	SetAnimationClipColorKey("NormalAttackLeft", 249, 0, 249);

	m_iDir = 1;

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
		m_iDir = -1;
		m_pAnimation->SetDefaultClip("IdleLeft");
	}

	if (KEYPRESS("MoveRight"))
	{
		MoveXFromSpeed(fDeltaTime, MD_FRONT);
		m_pAnimation->ChangeClip("RunRight");
		m_iDir = 1;
		m_pAnimation->SetDefaultClip("IdleRight");
	}

	if (KEYDOWN("Fire"))
	{
		Fire();

		if (m_iDir == -1)
		{
			m_pAnimation->ChangeClip("NormalAttackLeft");
		}
		else
		{
			m_pAnimation->ChangeClip("NormalAttackRight");
		}
	}

	if (KEYDOWN("Skill1"))
	{
		MessageBox(NULL, L"Skill1", L"Skill1", MB_OK);
	}
}

int CPlayer::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);
	
	if (m_bAttack && m_pAnimation->GetMotionEnd())
	{
		m_bAttack = false;
	}

	if(!m_bMove && !m_bAttack)
	{
		m_pAnimation->ReturnClip();
	}
	
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
	m_bAttack = true;

	CObj* pBullet = CObj::CreateCloneObj("Bullet", "PlayerBullet", m_pScene->GetSceneType(), m_pLayer);
	
	pBullet->AddCollisionFunction("BulletBody", CS_ENTER, (CBullet*)pBullet, &CBullet::Hit);

	//Pivot를 이용하여 총알 위치 재조정(가운데)
	POSITION tPos;

	if (m_iDir == -1)
	{
		tPos.x = GetLeft() + pBullet->GetSize().x * pBullet->GetPivot().x;
	}
	else
	{
		tPos.x = GetRight() + pBullet->GetSize().x * pBullet->GetPivot().x;
	}

	tPos.y = GetCenter().y;

	pBullet->SetPos(tPos);

	if (m_iDir == -1)
	{
		((CMoveObj*)pBullet)->SetAngle(PI);
	}

	SAFE_RELEASE(pBullet);
}
