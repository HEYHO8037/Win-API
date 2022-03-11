#include "Obj.h"



CObj::CObj()
{
}

CObj::CObj(const CObj & obj)
{
	*this = obj;
}

CObj::~CObj()
{
}

void CObj::SetScene(CScene* pScene)
{
	m_pScene = pScene;
}

void CObj::SetLayer(CLayer* pLayer)
{
	m_pLayer = pLayer;
}

CScene * CObj::GetScene() const
{
	return m_pScene;
}

CLayer * CObj::GetLayer() const
{
	return m_pLayer;
}

void CObj::SetTag(const string& strTag)
{
	m_strTag = strTag;
}

void CObj::SetPos(const POSITION & tPos)
{
	m_tPos.x = tPos.x;
	m_tPos.y = tPos.y;
}

void CObj::SetPos(float x, float y)
{
	m_tPos.x = x;
	m_tPos.y = y;
}

void CObj::SetSize(const _SIZE & tSize)
{
	m_tSize.x = tSize.x;
	m_tSize.y = tSize.y;
}

void CObj::SetSize(float x, float y)
{
	m_tSize.x = x;
	m_tSize.y = y;
}

string CObj::GetTag() const
{
	return m_strTag;
}

POSITION CObj::GetPosition() const
{
	return m_tPos;
}

_SIZE CObj::GetSize() const
{
	return m_tSize;
}

void CObj::Input(float fDeltaTime)
{
}

int CObj::Update(float fDeltaTime)
{
	return 0;
}

int CObj::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CObj::Collision(float fDeltaTime)
{
}

void CObj::Render(HDC hDC, float fDeltaTime)
{
}
