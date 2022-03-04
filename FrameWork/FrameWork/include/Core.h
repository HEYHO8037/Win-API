#pragma once

#include "Game.h"

class CCore
{
private:
	static CCore* m_pInst;

public:
	static CCore* GetInst();
	static void DestroyInst();

private:
	CCore();
	~CCore();

private:
	HINSTANCE m_hInst;
	HWND m_hWnd;
	RESOLUTION m_tRS;
	static bool m_bLoop;
	
public:
	bool Init(HINSTANCE hInst);
	int Run();

private:
	ATOM MyRegisterClass();
	BOOL Create();

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};