#include "Ref.h"



CRef::CRef()
	: m_iRef(1),
	  m_bEnable(true),
	  m_bLife(true)
{
}


CRef::~CRef()
{
}

void CRef::AddRef()
{
	++m_iRef;
}

int CRef::Release()
{
	--m_iRef;

	if (0 == m_iRef)
	{
		delete this;
		return 0;
	}

	return m_iRef;
}

void CRef::SetEnable(bool bEnable)
{
	m_bEnable = bEnable;
}

void CRef::Die()
{
	m_bLife = false;
}

bool CRef::GetEnable() const
{
	return m_bEnable;
}

bool CRef::GetLife() const
{
	return m_bLife;
}
