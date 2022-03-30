#pragma once
#include "Collider.h"

class CColliderSphere :
	public CCollider
{
protected:
	friend class CObj;

protected:
	CColliderSphere();
	CColliderSphere(const CColliderSphere& coll);
	~CColliderSphere();

private:
	SPHERE m_tInfo;
	SPHERE m_tWorldInfo;

public:
	void SetSphere(const POSITION& tCenter, float fRadius);
	SPHERE GetInfo() const;
	SPHERE GetWorldInfo() const;

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual bool Collision(CCollider* pDest);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CColliderSphere* Clone();
};

