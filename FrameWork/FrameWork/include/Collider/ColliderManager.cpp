#include "ColliderManager.h"
#include "../Object/Obj.h"

DEFINITION_SINGLE(CColliderManager)

CColliderManager::CColliderManager()
{
}


CColliderManager::~CColliderManager()
{
}

void CColliderManager::AddObject(CObj * pObj)
{
	if (pObj->CheckCollider())
	{
		m_CollisionList.push_back(pObj);
	}
	else
	{

	}
}

void CColliderManager::Collision(float fDeltaTime)
{
	if (m_CollisionList.size() < 2)
	{
		m_CollisionList.clear();
		return;
	}

	//오브젝트간 충돌처리를 한다.
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_CollisionList.end();
	--iterEnd;

	for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter)
	{
		list<CObj*>::iterator iter1 = iter;
		++iter1;

		list<CObj*>::iterator iter1End = m_CollisionList.end();

		for (; iter1 != iter1End; ++iter1)
		{
			Collision(*iter, *iter1, fDeltaTime);
		}

	}


	m_CollisionList.clear();
}

bool CColliderManager::Collision(CObj * pSrc, CObj * pDest, float fDeltaTime)
{
	const list<CCollider*>* pSrcList = pSrc->GetColliderList();
	const list<CCollider*>* pDestList = pDest->GetColliderList();

	list<CCollider*>::const_iterator iterSrc;
	list<CCollider*>::const_iterator iterSrcEnd = pSrcList->end();

	list<CCollider*>::const_iterator iterDest;
	list<CCollider*>::const_iterator iterDestEnd = pDestList->end();

	bool bCollision = false;

	for (iterSrc = pSrcList->begin(); iterSrc != iterSrcEnd; ++iterSrc)
	{
		for (iterDest = pDestList->begin(); iterDest != iterDestEnd; ++iterDest)
		{

		}

	}


	return bCollision;
}
