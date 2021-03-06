#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual	void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void SetBulletList(list<class CBullet*>* list);

private:
	void		Key_Input(void);

private:
	float m_fAngle;
	list<CBullet*>* m_pBulletList;
};

