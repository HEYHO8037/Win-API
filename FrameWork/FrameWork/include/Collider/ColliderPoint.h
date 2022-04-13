#pragma once
#include "Collider.h"
class CColliderPoint :
	public CCollider
{
protected:
	friend class CObj;

protected:
	CColliderPoint();
	CColliderPoint(const CColliderPoint& coll);
	~CColliderPoint();

protected:
	POSITION m_tPos;
	POSITION m_tDist;

public:
	POSITION GetPoint() const;
	void SetDistance(float x, float y);
	void SetDistance(const POSITION& tDist);


public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual bool Collision(CCollider* pDest);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CColliderPoint* Clone();
};

