#pragma once
#include "Obj.h"
class CBullet :
	public CObj
{
public:
	CBullet();
	CBullet(INFO& info, eDir dir);
	virtual ~CBullet();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual	void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	RECT GetRect() const;

private:
	eDir m_eDir;
};

