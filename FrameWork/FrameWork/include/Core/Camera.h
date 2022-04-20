#pragma once

#include "../Game.h"
class CCamera
{
private:
	POSITION m_tPos;
	RESOLUTION m_tClientRS;
	RESOLUTION m_tWorldRS;
	POSITION m_tPivot;
	class CObj* m_pTarget;

public:
	void SetTarget(class CObj* pObj);
	void SetPivot(const POSITION& tPivot);
	void SetPivot(float x, float y);
	void SetPos(const POSITION& tPos);
	void SetPos(float x, float y);
	void SetClientResolution(const RESOLUTION& tRS);
	void SetClientResolution(float x, float y);
	void SetWorldResolution(const RESOLUTION& tRS);
	void SetWorldResolution(float x, float y);

public:
	POSITION GetPos() const;
	RESOLUTION GetClientRS() const;

public:
	bool Init(const POSITION& tPos, const RESOLUTION& tClientRS, const RESOLUTION& tWorldRS);
	void Input(float fDeltaTime);
	void Update(float fDeltaTime);
	void Scroll(float x, float y);

	DECLARE_SINGLE(CCamera)
};

