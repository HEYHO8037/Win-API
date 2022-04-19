#include "MapEditScene.h"
#include "../Object/Stage.h"
#include "Layer.h"
#include "../Core/Camera.h"
#include "../Collider/ColliderRect.h"
#include "../Core.h"
#include "SceneManager.h"
#include "StartScene.h"


CMapEditScene::CMapEditScene()
{
}


CMapEditScene::~CMapEditScene()
{
}

bool CMapEditScene::Init()
{
	GET_SINGLE(CCamera)->SetWorldResolution(5200, 5200);

	CLayer* pStageLayer = FindLayer("Stage");

	CStage* pStage = CObj::CreateObj<CStage>("Stage", pStageLayer);

	pStage->CreateTile(100, 100, 52, 52, "Tile0", L"Tile/BaseTile.bmp");
	
	SAFE_RELEASE(pStage);

	return true;
}
