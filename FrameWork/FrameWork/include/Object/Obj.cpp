#include "Obj.h"
#include "../Scene/Layer.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"
#include "../Resources/ResourcesManager.h"
#include "../Resources/Texture.h"
#include "../Core/Camera.h"
#include "../Collider/Collider.h"
#include "../Animation/Animation.h"


list<CObj*> CObj::m_ObjectList;

CObj::CObj()
	: m_pTexture(nullptr),
	  m_pAnimation(nullptr),
	  m_bIsPhysics(false),
	  m_fGravityTime(0.f)
{
}

CObj::CObj(const CObj & obj)
{
	*this = obj;

	if (obj.m_pAnimation)
	{
		m_pAnimation = obj.m_pAnimation->Clone();
	}

	m_fGravityTime = 0.f;

	if (m_pTexture)
	{
		m_pTexture->AddRef();
	}

	m_ColliderList.clear();

	list<CCollider*>::const_iterator iter;
	list<CCollider*>::const_iterator iterEnd = obj.m_ColliderList.end();

	for (iter = obj.m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		CCollider* pColl = (*iter)->Clone();
		
		pColl->SetObj(this);

		m_ColliderList.push_back(pColl);
	}


}

CObj::~CObj()
{
	SAFE_RELEASE(m_pAnimation);
	Safe_Release_VecList(m_ColliderList);
	SAFE_RELEASE(m_pTexture);
}

void CObj::AddObj(CObj * pObj)
{
	pObj->AddRef();
	m_ObjectList.push_back(pObj);
}

CObj * CObj::FindObject(const string & strTag)
{
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjectList.end();

	for (iter = m_ObjectList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			(*iter)->AddRef();
			return *iter;
		}
	}

	return nullptr;
}

void CObj::EraseObj(CObj * pObj)
{
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjectList.end();

	for (iter = m_ObjectList.begin(); iter != iterEnd; ++iter)
	{
		if (*iter == pObj)
		{
			SAFE_RELEASE((*iter));
			iter = m_ObjectList.erase(iter);
			return;
		}
	}
}

void CObj::EraseObj(const string & strTag)
{
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjectList.end();

	for (iter = m_ObjectList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			SAFE_RELEASE((*iter));
			iter = m_ObjectList.erase(iter);
			return;
		}
	}
}

void CObj::EraseObj()
{
	Safe_Delete_VecList(m_ObjectList);
}

void CObj::ClearGravity()
{
	m_fGravityTime = 0.f;
}

void CObj::SetPhysics(bool bPhysics)
{
	m_bIsPhysics = bPhysics;
}

bool CObj::GetPhysics() const
{
	return m_bIsPhysics;
}

CAnimation * CObj::CreateAnimation(const string & strTag)
{
	SAFE_RELEASE(m_pAnimation);

	m_pAnimation = new CAnimation();

	m_pAnimation->SetTag(strTag);
	if (!m_pAnimation->Init())
	{
		SAFE_RELEASE(m_pAnimation);
		return nullptr;
	}

	return m_pAnimation;
}

const list<class CCollider*>* CObj::GetColliderList() const
{
	return &m_ColliderList;
}

bool CObj::CheckCollider()
{
	return !m_ColliderList.empty();
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

void CObj::SetPivot(const _SIZE & tPivot)
{
	m_tPivot = tPivot;
}

void CObj::SetPivot(float x, float y)
{
	m_tPivot.x = x;
	m_tPivot.y = y;
}

void CObj::SetTexture(CTexture * pTexture)
{
	SAFE_RELEASE(m_pTexture);
	m_pTexture = pTexture;

	if (pTexture)
	{
		pTexture->AddRef();
	}
}

void CObj::SetTexture(const string & strKey, const wchar_t * pFileName, const string & strPathKey)
{
	SAFE_RELEASE(m_pTexture);
	m_pTexture = GET_SINGLE(CResourcesManager)->LoadTexture(strKey, pFileName, strPathKey);

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

POSITION CObj::GetPivot() const
{
	return m_tPivot;
}

float CObj::GetLeft() const
{
	return m_tPos.x - m_tSize.x * m_tPivot.x;
}

float CObj::GetRight() const
{
	return GetLeft() + m_tSize.x;
}

float CObj::GetTop() const
{
	return m_tPos.y - m_tSize.y * m_tPivot.y;
}

float CObj::GetBottom() const
{
	return GetTop() + m_tSize.y;
}

POSITION CObj::GetCenter() const
{
	return POSITION(GetLeft() + m_tSize.x / 2.f, GetTop() + m_tSize.y / 2.f);
}

void CObj::Input(float fDeltaTime)
{
}

int CObj::Update(float fDeltaTime)
{	
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(fDeltaTime); 

		if (!(*iter)->GetLife())
		{
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else
		{
			++iter;
		}
	}

	return 0;
}

int CObj::LateUpdate(float fDeltaTime)
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->LateUpdate(fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else
		{
			++iter;
		}
	}

	return 0;
}

void CObj::Collision(float fDeltaTime)
{
}

void CObj::Render(HDC hDC, float fDeltaTime)
{
	if (m_pTexture)
	{
		//Pivot을 통해 이미지 위치 재 조정
		POSITION tPos = m_tPos - m_tSize * m_tPivot;
		tPos -= GET_SINGLE(CCamera)->GetPos();

		if (m_pTexture->GetColorKeyEnable())
		{
			TransparentBlt(hDC, tPos.x, tPos.y, m_tSize.x, m_tSize.y,
				m_pTexture->GetDC(), 0, 0, m_tSize.x, m_tSize.y,
				m_pTexture->GetColorKey());
		}
		else
		{
			BitBlt(hDC, tPos.x, tPos.y,
				m_tSize.x, m_tSize.y, m_pTexture->GetDC(),
				0, 0, SRCCOPY);
		}
	}

	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Render(hDC, fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else
		{
			++iter;
		}
	}
}

CObj* CObj::CreateCloneObj(const string& strPrototypeKey, const string& strKey, class CLayer* pLayer)
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetScene();
	CObj* pProto = pScene->FindPrototype(strPrototypeKey);

	if (!pProto)
	{
		return nullptr;
	}

	CObj* pObj = pProto->Clone();
	pObj->SetTag(strKey);

	if (pLayer)
	{
		pLayer->AddObject(pObj);
	}

	AddObj(pObj);

	return pObj;

}
