#pragma once
#include "MoveObj.h"
	
class CMinion :
	public CMoveObj
{
private:
	friend class CObj;

private:
	MOVE_DIR m_eDir;
	float m_fFireTime;
	float m_fFireLimitTime;

private:
	CMinion();
	CMinion(const CMinion& minion);
	virtual ~CMinion();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CMinion* Clone();

private:
	void Fire();
};

