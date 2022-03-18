#pragma once

#include "../Ref.h"

class CObj : public CRef
{
protected:
	friend class CScene;
public:
	CObj();
	CObj(const CObj& obj);
	virtual ~CObj();

private:
	static list<CObj*> m_ObjectList;

public:
	static void AddObj(CObj* pObj);
	static CObj* FindObject(const string& strTag);
	static void EraseObj(CObj* pObj);
	static void EraseObj(const string& strTag);
	static void EraseObj();


protected:
	string m_strTag;
	POSITION m_tPos;
	_SIZE m_tSize;
	POSITION m_tPivot;

protected:
	class CScene* m_pScene;
	class CLayer* m_pLayer;

public:
	void SetScene(class CScene* pScene);
	void SetLayer(class CLayer* pLayer);
	class CScene* GetScene() const;
	class CLayer* GetLayer() const;

public:
	void SetTag(const string& strTag);
	void SetPos(const POSITION& tPos);
	void SetPos(float x, float y);
	void SetSize(const _SIZE& tSize);
	void SetSize(float x, float y);

public:
	string GetTag() const;
	POSITION GetPosition() const;
	_SIZE GetSize() const;

public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CObj* Clone() = 0;

public:
	template <typename T>
	static T* CreateObj(const string& strTag, class CLayer* pLayer = nullptr)
	{
		T* pObj = new T;

		pObj->SetTag(strTag);

		if (!pObj->Init())
		{
			SAFE_RELEASE(pObj);
			return nullptr;
		}

		if (pLayer)
		{
			pLayer->AddObject(pObj);
		}

		AddObj(pObj);

		return pObj;
	}

public:
	static CObj* CreateCloneObj(const string& strPrototypeKey, const string& strKey, class CLayer* pLayer = nullptr);


};

