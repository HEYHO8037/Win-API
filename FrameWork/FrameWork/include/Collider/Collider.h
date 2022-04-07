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
	list<CCollider*> m_CollisionList;
	list<function<void(CCollider*, CCollider*, float)>> m_FuncList[CS_END];
	POSITION m_HitPoint;

public:
	POSITION GetHitPoint() const;
	void SetHitPoint(const POSITION& tPos);

public:
	template <typename T>
	void AddCollisionFunction(COLLISION_STATE eState, T* pObj, void(T::*pFunc)(CCollider*, CCollider*, float))
	{
		function<void(CCollider*, CCollider*, float)> func;

		func = bind(pFunc, pObj, placeholders::_1, placeholders::_2, placeholders::_3);

		m_FuncList[eState].push_back(func);
	}

	void CallFunction(COLLISION_STATE eState, CCollider* pDest, float fDeltaTime);

public:
	void AddCollider(CCollider* pCollider);
	bool CheckCollisionList(CCollider* pCollider);
	void EraseCollisionList(CCollider* pCollider);

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
	bool CollisionRectToSphere(const RECTANGLE& src, const SPHERE& dest);
	bool CollisionSphereToSphere(const SPHERE& src, const SPHERE& dest);
	bool CollisionRectToPixel(const RECTANGLE& src, const vector<PIXEL>& vecPixel, int iWidth, int iHeight);
};

