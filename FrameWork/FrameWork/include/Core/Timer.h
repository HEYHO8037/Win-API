#pragma once
#include "../Game.h"

class CTimer
{
private:
	HWND m_hWnd;
	LARGE_INTEGER m_tSecond;
	LARGE_INTEGER m_tTime;
	float m_fDeltaTime;
	float m_fTimeScale;
	float m_fFPS;
	float m_fFPSTime;
	int m_iFrame;

public:
	float GetDeltaTime() const;
	float GetFPS() const;
	float GetTimeScale() const;
	void SetTimeScale(float fTimeScale);

public:
	bool Init(HWND hWnd);
	void Update();


	DECLARE_SINGLE(CTimer)

};

