#pragma once

#include "../Game.h"

class CLayer
{
	friend class CScene;

private:
	CLayer();

public:
	~CLayer();

private:
	class CScene* m_pScene;
	string m_strTag;
	int m_iZOrder;
	list<class CObj*> m_ObjList;

public:
	void SetTag(const string& strTag);
	void SetZOrder(int iZorder);
	void SetScene(class CScene* pScene);
	int GetZOrder() const;
	string GetTag() const;
	CScene* GetScene() const;

public:
	void AddObject(class CObj* pObj);

public:
	void Input(float fDeltaTime);
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDC, float fDeltaTime);

};

