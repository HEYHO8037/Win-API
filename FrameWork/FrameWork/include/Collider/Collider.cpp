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

POSITION CCollider::GetHitPoint() const
{
	return m_HitPoint;
}

void CCollider::SetHitPoint(const POSITION & tPos)
{
	m_HitPoint = tPos;
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
	if ((src.l <= dest.tCenter.x && dest.tCenter.x <= src.r) ||
		(src.t <= dest.tCenter.y && dest.tCenter.y <= src.b))
	{
		RECTANGLE tRC = src;
		tRC.l -= dest.fRadius;
		tRC.t -= dest.fRadius;
		tRC.r += dest.fRadius;
		tRC.b += dest.fRadius;

		if (dest.tCenter.x < tRC.l)
		{
			return false;
		}
		else if (dest.tCenter.x > tRC.r)
		{
			return false;
		}
		else if (dest.tCenter.y > tRC.b)
		{
			return false;
		}
		else if (dest.tCenter.y < tRC.t)
		{
			return false;
		}

		return true;
	}

	//사각형의 4개의 점이 하나라도 원안에 있을 경우 충돌이다.
	POSITION tPos[4];
	tPos[0] = POSITION(src.l, src.t);
	tPos[1] = POSITION(src.r, src.t);
	tPos[2] = POSITION(src.l, src.b);
	tPos[3] = POSITION(src.r, src.b);

	for (int i = 0; 4 > i; ++i)
	{
		float fDist = CMath::Distance(tPos[i], dest.tCenter);

		if (fDist <= dest.fRadius)
		{
			return true;
		}
	}

	return false;
}

bool CCollider::CollisionSphereToSphere(const SPHERE & src, const SPHERE & dest)
{
	//원 끼리 충돌 시 두 원의 중점의 서로의 길이가 두 원의 반지름을 더한 값보다 작으면 충돌

	float fDist = CMath::Distance(src.tCenter, dest.tCenter);

	return fDist <= src.fRadius + dest.fRadius;
}

bool CCollider::CollisionSphereToPixel(const SPHERE & src, const vector<PIXEL>& vecPixel, int iWidth, int iHeight)
{
	return false;
}

bool CCollider::CollisionSphereToPoint(const SPHERE & src, const POSITION & dest)
{
	return CMath::Distance(dest, src.tCenter) <= src.fRadius;
}

bool CCollider::CollisionPixelToPoint(const vector<PIXEL>& vecPixel, int iWidth, int iHeight, const POSITION & dest)
{
	if (dest.y < 0 || dest.x < 0 || dest.x >= iWidth || dest.y >= iHeight)
	{
		return false;
	}


	int idx = dest.y * iWidth + (int)dest.x;
	const PIXEL& pixel = vecPixel[idx];

	if (pixel.r == 255 && pixel.g == 0 && pixel.b == 255)
	{
		m_HitPoint = dest;
		return true;
	}

	return false;
}

bool CCollider::CollisionRectToPixel(const RECTANGLE & src, const vector<PIXEL>& vecPixel, int iWidth, int iHeight)
{
	m_HitPoint.x = -1;
	m_HitPoint.y = -1;

	int iStartX, iEndX;
	int iStartY, iEndY;

	iStartX = src.l < 0 ? 0 : src.l;
	iEndX = src.r >= iWidth ? iWidth - 1 : src.r;

	iStartY = src.t < 0 ? 0 : src.t;
	iEndY = src.b >= iHeight ? iHeight - 1 : src.b;

	for (int i = iStartY; i <= iEndY; ++i)
	{
		for (int j = iStartX; j <= iEndX; ++j)
		{
			int idx = i * iWidth + j;
			const PIXEL& pixel = vecPixel[idx];
			
			if (pixel.r == 255 && pixel.g == 0 && pixel.b == 255)
			{
				m_HitPoint.x = j;
				m_HitPoint.y = i;

				return true;
			}
		}
	}

	return false;
}

bool CCollider::CollisionRectToPoint(const RECTANGLE & src, const POSITION & dest)
{
	if (dest.x < src.l)
	{
		return false;
	}
	else if (dest.x > src.r)
	{
		return false;
	}
	else if (dest.y < src.t)
	{
		return false;
	}
	else if (dest.y > src.b)
	{
		return false;
	}

	return true;
}
