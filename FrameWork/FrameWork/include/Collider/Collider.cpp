#include "Collider.h"
#include "../Object/Obj.h"
#include "../Core/Math.h"


CCollider::CCollider()
{
}

CCollider::CCollider(const CCollider & coll)
{
	*this = coll;
}


CCollider::~CCollider()
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_CollisionList.end();

	for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->EraseCollisionList(this);
	}
}


void CCollider::CallFunction(COLLISION_STATE eState, CCollider* pDest, float fDeltaTime)
{
	list<function<void(CCollider*, CCollider*, float)>>::iterator iter;
	list<function<void(CCollider*, CCollider*, float)>>::iterator iterEnd = m_FuncList[eState].end();

	for (iter = m_FuncList[eState].begin(); iter != iterEnd; ++iter)
	{
		(*iter)(this, pDest, fDeltaTime);
	}

}

void CCollider::AddCollider(CCollider * pCollider)
{
	m_CollisionList.push_back(pCollider);
}

bool CCollider::CheckCollisionList(CCollider * pCollider)
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_CollisionList.end();

	for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter) == pCollider)
		{
			return true;
		}
	}
	return false;
}

void CCollider::EraseCollisionList(CCollider * pCollider)
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_CollisionList.end();

	for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter) == pCollider)
		{
			m_CollisionList.erase(iter);
			break;
		}
	}

}

COLLIDER_TYPE CCollider::GetColliderType() const
{
	return m_eCollType;
}

CObj * CCollider::GetObj() const
{
	return m_pObj;
}

void CCollider::SetObj(CObj * pObj)
{
	m_pObj = pObj;
}

void CCollider::Input(float fDeltaTime)
{
}

int CCollider::Update(float fDeltaTime)
{
	return 0;
}

int CCollider::LateUpdate(float fDeltaTime)
{
	return 0;
}

bool CCollider::Collision(CCollider* pDest)
{
	return false;
}

void CCollider::Render(HDC hDC, float fDeltaTime)
{
}

bool CCollider::CollisionRectToRect(const RECTANGLE & src, const RECTANGLE & dest)
{
	if (src.l > dest.r)
	{
		return false;
	}
	else if (src.r < dest.l)
	{
		return false;
	}
	else if (src.t > dest.b)
	{
		return false;
	}
	else if (src.b < dest.t)
	{
		return false;
	}

	return true;
}

bool CCollider::CollisionRectToSphere(const RECTANGLE & src, const SPHERE & dest)
{
	// 원의 중점 X좌표가 사각형의 가로 영역 안에 있는지,
	// 원의 중점 Y좌표가 사각형의 세로 영역 안에 있는지 체크한다.
	// 둘 중 하나라도 맞다면 사각형의 위 아래 좌 우 영역안에 존재한다는 것이다.

	return false;
}

bool CCollider::CollisionSphereToSphere(const SPHERE & src, const SPHERE & dest)
{
	//원 끼리 충돌 시 두 원의 중점의 서로의 길이가 두 원의 반지름을 더한 값보다 작으면 충돌

	float fDist = CMath::Distance(src.tCenter, dest.tCenter);

	return fDist <= src.fRadius + dest.fRadius;
}
