#pragma once
#include "UI.h"
class CMouse :
	public CUI
{
private:
	friend class CObj;
	friend class CScene;

private:
	POINT m_tMove;

private:
	CMouse();
	CMouse(const CMouse& mouse);
	~CMouse();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CMouse* Clone();
};

