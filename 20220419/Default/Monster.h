#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	CMonster();
	virtual ~CMonster();
	
public:
	virtual	void Initialize(void);
	virtual	void Update(void);
	virtual	void Late_Update(void);
	virtual	void Render(HDC hDC);
	virtual	void Release(void);

public:
	RECT GetRect() const;

private:
	void MoveLeft();
	void MoveRight();
	void CheckCollision();

private:
	bool m_bIsLeft;
};

