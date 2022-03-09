#include "Layer.h"
#include "../Object/Obj.h"


CLayer::CLayer()
	: m_iZOrder(0),
	  m_strTag(""),
	  m_pScene(nullptr)
{
}


CLayer::~CLayer()
{
	Safe_Release_VecList(m_ObjList);
}

void CLayer::SetTag(const string& strTag)
{
	m_strTag = strTag;
}

void CLayer::SetZOrder(int iZOrder)
{
	m_iZOrder = iZOrder;
}

void CLayer::SetScene(CScene * pScene)
{
	m_pScene = pScene;
}

int CLayer::GetZOrder() const
{
	return m_iZOrder;
}

string CLayer::GetTag() const
{
	return m_strTag;
}

CScene * CLayer::GetScene() const
{
	return m_pScene;
}
