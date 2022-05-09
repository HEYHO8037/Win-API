#include "stdafx.h"
#include "MainGame.h"
#include "LineMgr.h"
#include "KeyMgr.h"

CMainGame::CMainGame()
	: m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 64);
	m_iFPS = 0;
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);
	

	CLineMgr::Get_Instance()->Initialize();
}

void CMainGame::Update(void)
{
	CLineMgr::Get_Instance()->Update();
	
}

void CMainGame::Late_Update(void)
{
	CLineMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	CLineMgr::Get_Instance()->Render(m_hDC);

	

}

void CMainGame::Release(void)
{
	CLineMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);	
}

