#pragma once
#include "StaticObj.h"
class CTile :
	public CStaticObj
{
private:
	friend class CObj;
	friend class CStage;

private:
	CTile();
	CTile(const CTile& stage);
	~CTile();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CTile* Clone();
};

