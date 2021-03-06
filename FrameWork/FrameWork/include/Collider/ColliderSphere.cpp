#include "ColliderSphere.h"
#include "../Object/Obj.h"
#include "ColliderRect.h"
#include "ColliderPixel.h"
#include "ColliderPoint.h"


CColliderSphere::CColliderSphere()
{
	m_eCollType = CT_SPHERE;
}

CColliderSphere::CColliderSphere(const CColliderSphere & coll)
	:CCollider(coll)
{
	m_tInfo = coll.m_tInfo;
}


CColliderSphere::~CColliderSphere()
{
}

void CColliderSphere::SetSphere(const POSITION & tCenter, float fRadius)
{
	m_tInfo.tCenter = tCenter;
	m_tInfo.fRadius = fRadius;
}

SPHERE CColliderSphere::GetInfo() const
{
	return m_tInfo;
}

SPHERE CColliderSphere::GetWorldInfo() const
{
	return m_tWorldInfo;
}

bool CColliderSphere::Init()
{
	return true;
}

void CColliderSphere::Input(float fDeltaTime)
{
	CCollider::Input(fDeltaTime);
}

int CColliderSphere::Update(float fDeltaTime)
{
	CCollider::Update(fDeltaTime);
	return 0;
}

int CColliderSphere::LateUpdate(float fDeltaTime)
{
	CCollider::LateUpdate(fDeltaTime);

	POSITION tPos = m_pObj->GetPosition();

	m_tWorldInfo.tCenter = tPos + m_tInfo.tCenter;
	m_tWorldInfo.fRadius = m_tInfo.fRadius;


	return 0;
}

bool CColliderSphere::Collision(CCollider * pDest)
{
	switch (pDest->GetColliderType())
	{
	case CT_SPHERE:
		return CollisionSphereToSphere(m_tWorldInfo, ((CColliderSphere*)pDest)->GetWorldInfo());
	case CT_RECT:
		return CollisionRectToSphere(((CColliderRect*)pDest)->GetWorldInfo(), m_tWorldInfo); 
	case CT_POINT:
		return CollisionSphereToPoint(m_tWorldInfo, ((CColliderPoint*)pDest)->GetPoint());
	}

	return false;
}

void CColliderSphere::Render(HDC hDC, float fDeltaTime)
{

	CCollider::Render(hDC, fDeltaTime);
}

CColliderSphere * CColliderSphere::Clone()
{
	return new CColliderSphere(*this);
}
