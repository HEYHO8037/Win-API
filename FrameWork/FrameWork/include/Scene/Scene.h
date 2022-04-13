#pragma once
#include "../Game.h"

class CScene
{
protected:
	friend class CSceneManager;

protected:
	CScene();
	virtual ~CScene() = 0;

private:
	static unordered_map<string, class CObj*> m_mapPrototype[SC_END];

protected:
	list<class CLayer*> m_LayerList;
	SCENE_CREATE m_eSceneCreate;

public:
	void SetSceneType(SCENE_CREATE eType);
	SCENE_CREATE GetSceneType();
	
public:
	class CLayer* CreateLayer(const string& strTag, int iZOrder = 0);
	class CLayer* FindLayer(const string& strTag);
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);

public:
	static void ErasePrototype(SCENE_CREATE sc);
	static void ErasePrototype(const string& strTag, SCENE_CREATE sc);

	template <typename T>
	static T* CreatePrototype(const string& strTag, SCENE_CREATE sc)
	{
		T* pObj = new T;

		pObj->SetTag(strTag);

		if (!pObj->Init())
		{
			SAFE_RELEASE(pObj);
			return nullptr;
		}

		pObj->AddRef();
		m_mapPrototype[sc].insert(make_pair(strTag, pObj));

		return pObj;
	}

	static CObj* FindPrototype(const string& strKey, SCENE_CREATE sc);
	static void ChangePrototype();

public:
	static bool LayerSort(class CLayer* pL1, class CLayer* pL2);
	
};

