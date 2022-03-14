#pragma once

#include "Obj.h"

class CMoveObj : public CObj
{
protected:
	CMoveObj();
	CMoveObj(const CMoveObj& obj);
	virtual ~CMoveObj();
	
private:
	float m_fAngle;

public:
	void Move(float x, float y);
	void Move(float x, float y, float fDeltaTime);
	void Move(const POSITION& tMove);
	void Move(const POSITION& tMove, float fDeltaTime);
	void MoveX(float x);
	void MoveX(float x, float fDeltaTime);
	void MoveY(float y);
	void MoveY(float y, float fDeltaTime);
	void MoveAngle(float fSpeed);
	void MoveAngle(float fSpeed, float fTime);


public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

