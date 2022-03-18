#pragma once
#include "MoveObj.h"
class CBullet :
	public CMoveObj
{
public:
	CBullet();
	CBullet(const CBullet& bullet);
	~CBullet();

private:
	float m_fLimitDist;
	float m_fDist;

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CBullet* Clone();
};

