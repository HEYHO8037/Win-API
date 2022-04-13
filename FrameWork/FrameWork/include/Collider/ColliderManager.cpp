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

	//������Ʈ�� �浹ó���� �Ѵ�.
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

				//�浹��Ͽ��� ������ �浹�� ���� ���ٸ�
				//ó�� �� �浹�ߴٴ� �ǹ��̴�.

				if (!(*iterSrc)->CheckCollisionList(*iterDest))
				{
					//���� ������ �浹������� �߰��Ѵ�.
					(*iterSrc)->AddCollider(*iterDest);
					(*iterDest)->AddCollider(*iterSrc);

					(*iterSrc)->CallFunction(CS_ENTER, *iterDest, fDeltaTime);
					(*iterDest)->CallFunction(CS_ENTER, *iterSrc, fDeltaTime);

				}
				else
				{
					//���� �浹������ �ִٸ� ��� �浹������ ���̴�.
					(*iterSrc)->CallFunction(CS_STAY, *iterDest, fDeltaTime);
					(*iterDest)->CallFunction(CS_STAY, *iterSrc, fDeltaTime);

				}

			}
			else if ((*iterSrc)->CheckCollisionList(*iterDest))
			{
				// ���� �浹�� �ȵ� ���¿��� ������ �浹 �ǰ� �־��ٸ�
				// ���� �� �浹���¿��� ����ٴ� �ǹ��̴�.
				// ���� �浹�� �ȵǹǷ� �浹 ��Ͽ��� �����ش�.
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
