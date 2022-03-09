#include "Obj.h"



CObj::CObj()
	: m_iRef(1)
{
}


CObj::~CObj()
{
}

void CObj::SetTag(const string& strTag)
{
	m_strTag = strTag;
}

void CObj::SetPos(const POSITION & tPos)
{
	m_Pos.x = tPos.x;
	m_Pos.y = tPos.y;
}

void CObj::SetPos(float x, float y)
{
	m_Pos.x = x;
	m_Pos.y = y;
}

void CObj::SetSize(const _SIZE & tSize)
{
	m_Size.x = tSize.x;
	m_Size.y = tSize.y;
}

void CObj::SetSize(float x, float y)
{
	m_Size.x = x;
	m_Size.y = y;
}

string CObj::GetTag() const
{
	return m_strTag;
}

POSITION CObj::GetPosition() const
{
	return m_Pos;
}

_SIZE CObj::GetSize() const
{
	return m_Size;
}

void CObj::AddRef()
{
	m_iRef++;
}

int CObj::Release()
{
	--m_iRef;

	if (0 == m_iRef)
	{
		delete this;
		return 0;
	}

	return m_iRef;
}
