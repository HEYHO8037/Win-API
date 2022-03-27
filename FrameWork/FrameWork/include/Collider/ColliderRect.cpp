#include "ColliderRect.h"



CColliderRect::CColliderRect()
{
	m_eCollType = CT_RECT;
}

CColliderRect::CColliderRect(const CColliderRect & coll)
	: CCollider(coll)
{
}


CColliderRect::~CColliderRect()
{

}

COLLIDER_TYPE CColliderRect::GetColliderType() const
{
	return m_eCollType;
}

bool CColliderRect::Init()
{
	return false;
}

void CColliderRect::Input(float fDeltaTime)
{
}

int CColliderRect::Update(float fDeltaTime)
{
	return 0;
}

int CColliderRect::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CColliderRect::Collision(float fDeltaTime)
{
}

void CColliderRect::Render(HDC hDC, float fDeltaTime)
{
}

CColliderRect * CColliderRect::Clone()
{
	return new CColliderRect(*this);
}
