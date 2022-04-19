#pragma once
#include "Scene.h"
class CStartScene :
	public CScene
{
private:
	friend class CSceneManager;

private:
	CStartScene();
	~CStartScene();

public:
	virtual bool Init();

public:
	void StartButtonCallBack(float fTime);
	void EndButtonCallBack(float fTime);
	void EditButtonCallBack(float fTime);

};

