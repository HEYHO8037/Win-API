#pragma once
#include "../Ref.h"

class CCollider :
	public CRef
{
protected:
	friend class CObj;

protected:
	CCollider();
	CCollider(const CCollider& coll);
	virtual ~CCollider() = 0;

protected:
	COLLIDER_TYPE m_eCollType;
	class CObj* m_pObj;


public:
	COLLIDER_TYPE GetColliderType() const;
	class CObj* GetObj() const;

public:
	void SetObj(class CObj* pObj);


public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual bool Collision(CCollider* pDest);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CCollider* Clone() = 0;

protected:
	bool CollisionRectToRect(const RECTANGLE& src, const RECTANGLE& dest);
};

