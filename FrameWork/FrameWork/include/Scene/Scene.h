#pragma once
#include "../Game.h"

class CScene
{
protected:
	friend class CSceneManager;

protected:
	CScene();
	virtual ~CScene() = 0;

protected:
	list<class CLayer*> m_LayerList;
	
public:
	class CLayer* CreateLayer();
	virtual bool Init();
};

