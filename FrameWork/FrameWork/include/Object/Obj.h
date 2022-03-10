#pragma once

#include "../Game.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

protected:
	int m_iRef;

protected:
	string m_strTag;
	POSITION m_Pos;
	_SIZE m_Size;

public:
	void SetTag(const string& strTag);
	void SetPos(const POSITION& tPos);
	void SetPos(float x, float y);
	void SetSize(const _SIZE& tSize);
	void SetSize(float x, float y);

public:
	string GetTag() const;
	POSITION GetPosition() const;
	_SIZE GetSize() const;

public:
	void AddRef();
	int Release();

public:
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

