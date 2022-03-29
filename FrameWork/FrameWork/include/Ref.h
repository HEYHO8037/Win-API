#pragma once

#include "Game.h"

class CRef
{
public:
	CRef();
	virtual ~CRef() = 0;

protected:
	int m_iRef;
	bool m_bEnable;
	bool m_bLife;
	string m_strTag;

public:
	void AddRef();
	int Release();
	void SetEnable(bool bEnable);
	void Die();
	bool GetEnable() const;
	bool GetLife() const;
	string GetTag() const;
	void SetTag(const string& strTag);
};

