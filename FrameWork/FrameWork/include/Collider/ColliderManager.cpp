#include "ColliderManager.h"
#include "../Object/Obj.h"
#include "Collider.h"

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
  			if ((*iterSrc)->Collision(*iterDest))
			{
				bCollision = true;

				(*iterDest)->SetHitPoint((*iterSrc)->GetHitPoint());

				//충돌목록에서 이전에 충돌된 적이 없다면
				//처음 막 충돌했다는 의미이다.

				if (!(*iterSrc)->CheckCollisionList(*iterDest))
				{
					//서로 상대방을 충돌목록으로 추가한다.
					(*iterSrc)->AddCollider(*iterDest);
					(*iterDest)->AddCollider(*iterSrc);

					(*iterSrc)->CallFunction(CS_ENTER, *iterDest, fDeltaTime);
					(*iterDest)->CallFunction(CS_ENTER, *iterSrc, fDeltaTime);

				}
				else
				{
					//기존 충돌된적이 있다면 계속 충돌상태인 것이다.
					(*iterSrc)->CallFunction(CS_STAY, *iterDest, fDeltaTime);
					(*iterDest)->CallFunction(CS_STAY, *iterSrc, fDeltaTime);

				}

			}
			else if ((*iterSrc)->CheckCollisionList(*iterDest))
			{
				// 현재 충돌이 안된 상태에서 이전에 충돌 되고 있었다면
				// 이제 막 충돌상태에서 벗어났다는 의미이다.
				// 서로 충돌이 안되므로 충돌 목록에서 지워준다.
				(*iterSrc)->EraseCollisionList(*iterDest);
				(*iterDest)->EraseCollisionList(*iterSrc);

				(*iterSrc)->CallFunction(CS_LEAVE, *iterDest, fDeltaTime);
				(*iterDest)->CallFunction(CS_LEAVE, *iterSrc, fDeltaTime);


			}
		}
	}


	return bCollision;
}

void CColliderManager::Clear()
{
	m_CollisionList.clear();
}
