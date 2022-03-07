#pragma once
#include "../Game.h"

class CTimer
{
public:
	LARGE_INTEGER m_tSecond;
	LARGE_INTEGER m_tTime;
	float m_fDeltaTime;
	float m_fFPS;
	float m_fFPSTime;
	int m_iFrameMax;
	int m_iFrame;

public:
	float GetDeltaTime() const;
	float GetFPS() const;

public:
	bool Init();
	void Update();


	DECLARE_SINGLE(CTimer)

};

