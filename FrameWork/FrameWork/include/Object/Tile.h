#pragma once
#include "StaticObj.h"
class CTile :
	public CStaticObj
{
private:
	friend class CObj;
	friend class CStage;

private:
	CTile();
	CTile(const CTile& tile);
	~CTile();

private:
	TILE_OPTION m_eOption;

public:
	void SetTileOption(TILE_OPTION eOption);
	TILE_OPTION GetTileOption() const;

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CTile* Clone();
};

