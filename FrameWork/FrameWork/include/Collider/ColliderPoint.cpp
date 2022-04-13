#include "ColliderPoint.h"
#include "../Object/Obj.h"
#include "ColliderSphere.h"
#include "ColliderRect.h"
#include "ColliderPixel.h"



CColliderPoint::CColliderPoint()
{
	m_eCollType = CT_POINT;
}

CColliderPoint::CColliderPoint(const CColliderPoint & coll)
	: CCollider(coll)
{
	m_tDist = coll.m_tDist;
}


CColliderPoint::~CColliderPoint()
{
}

POSITION CColliderPoint::GetPoint() const
{
	return m_tPos;
}

void CColliderPoint::SetDistance(float x, float y)
{
	m_tDist.x = x;
	m_tDist.y = y;
}

void CColliderPoint::SetDistance(const POSITION & tDist)
{
	m_tDist = tDist;
}

bool CColliderPoint::Init()
{
	return true;
}

void CColliderPoint::Input(float fDeltaTime)
{
	CCollider::Input(fDeltaTime);
}

int CColliderPoint::Update(float fDeltaTime)
{
	CCollider::Update(fDeltaTime);
	return 0;
}

int CColliderPoint::LateUpdate(float fDeltaTime)
{
	CCollider::LateUpdate(fDeltaTime);

	POSITION tPos = m_pObj->GetPosition();

	m_tPos.x = tPos.x + m_tDist.x;
	m_tPos.y = tPos.y + m_tDist.y;

	return 0;
}

bool CColliderPoint::Collision(CCollider * pDest)
{
	switch (pDest->GetColliderType())
	{
	case CT_RECT:
		return CollisionRectToPoint(((CColliderRect*)pDest)->GetWorldInfo(), m_tPos);
	case CT_SPHERE:
		return CollisionSphereToPoint(((CColliderSphere*)pDest)->GetWorldInfo(), m_tPos);
	case CT_PIXEL:
		return CollisionPixelToPoint(((CColliderPixel*)pDest)->GetPixel(),
			((CColliderPixel*)pDest)->GetWidth(), ((CColliderPixel*)pDest)->GetHeight(), m_tPos);
	}

	return false;
}

void CColliderPoint::Render(HDC hDC, float fDeltaTime)
{
	CCollider::Render(hDC, fDeltaTime);
}

CColliderPoint * CColliderPoint::Clone()
{
	return new CColliderPoint(*this);
}
