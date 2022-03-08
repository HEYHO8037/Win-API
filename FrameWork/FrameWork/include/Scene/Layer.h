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

public:
	void SetTag(const string& strTag);
	void SetZOrder(int iZorder);
	void SetScene(class CScene* pScene);
	int GetZOrder() const;
	string GetTag() const;
	CScene* GetScene() const;

};

