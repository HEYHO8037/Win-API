#include "Ref.h"



CRef::CRef()
	: m_iRef(1)
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
