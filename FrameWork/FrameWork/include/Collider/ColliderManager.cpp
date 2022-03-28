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

	m_CollisionList.clear();
}
