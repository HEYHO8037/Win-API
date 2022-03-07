#include "Scene.h"
#include "Layer.h"

CScene::CScene()
{
}


CScene::~CScene()
{
	Safe_Delete_VecList(m_LayerList);
}

bool CScene::Init()
{
	return true;
}
