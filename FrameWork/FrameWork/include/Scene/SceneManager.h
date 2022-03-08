#pragma once
#include "../Game.h"

class CSceneManager
{
private:
	class CScene* m_pScene;
	class CScene* m_pNextScene;

public:
	bool Init();

public:
	template <typename T>
	T* CreateScene(SCENE_CREATE sc);
	DECLARE_SINGLE(CSceneManager)
};

template<typename T>
inline T * CSceneManager::CreateScene(SCENE_CREATE sc)
{
	T* pScene = new T;
	
	if (!pScene->Init())
	{
		SAFE_DELETE(pScene);
		return NULL;
	}

	switch (sc)
	{
	case SC_CURRENT:
		SAFE_DELETE(m_pScene);
		m_pScene = m_pScene;
		break;

	case SC_NEXT:
		SAFE_DELETE(m_pNextScene);
		m_pNextScene = m_pScene;
		break;
	}

	return pScene;
}