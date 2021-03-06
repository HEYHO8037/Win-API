#pragma once
#include "Collider.h"

class CColliderRect :
	public CCollider
{
protected:
	friend class CObj;

protected:
	CColliderRect();
	CColliderRect(const CColliderRect& coll);
	virtual ~CColliderRect();
	
private:
	RECTANGLE m_tInfo;
	RECTANGLE m_tWorldInfo;

public:
	void SetRect(float l, float t, float r, float b);
	RECTANGLE GetInfo() const;
	RECTANGLE GetWorldInfo() const;

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual bool Collision(CCollider* pDest);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CColliderRect* Clone();

};

