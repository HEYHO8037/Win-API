#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "Monster.h"
#include "Mouse.h"
#include "CollisionMgr.h"


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

#pragma region 복습

	/*if (!m_pPlayer)
	{
		//m_pPlayer = new CPlayer;
		//m_pPlayer->Initialize();
		m_pPlayer = CAbstractFactory<CPlayer>::Create();
	}
	dynamic_cast<CPlayer*>(m_pPlayer)->Set_BulletList(&m_BulletList);*/

#pragma endregion 복습

	m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_BulletList(&m_ObjList[OBJ_BULLET]);
	

	/*for (int i = 0; i < 5; ++i)
	{
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(float(rand() % 56 + 13) * 10, float(rand() % 30 + 13) * 10));
	}

	m_ObjList[OBJ_MOUSE].push_back(CAbstractFactory<CMouse>::Create());*/
}

void CMainGame::Update(void)
{
#pragma region 복습
	/*m_pPlayer->Update();

	for (auto iter = m_BulletList.begin(); iter != m_BulletList.end(); )
	{
		int iResult = (*iter)->Update();

		if (OBJ_DEAD == iResult)
		{
			Safe_Delete<CObj*>(*iter);
			iter = m_BulletList.erase(iter);
		}
		else
			++iter;
	}*/
#pragma endregion 복습

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
	
}

void CMainGame::Late_Update(void)
{
// /*
// 	m_pPlayer->Late_Update();
// 
// 	for (auto& iter : m_BulletList)
// 		iter->Late_Update();*/
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}

	//CCollisionMgr::Collision_Rect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);
	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);
}

void CMainGame::Render(void)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	Rectangle(m_hDC, 100, 100, WINCX - 100, WINCY - 100);

	/*m_pPlayer->Render(m_hDC);

	for (auto& iter : m_BulletList)
		iter->Render(m_hDC);*/
	
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(m_hDC);
	}


	// 폰트 출력

	//lstrcpy(m_szFPS, L"Hello");
	//TextOut(m_hDC, 50, 50, m_szFPS, lstrlen(m_szFPS));
	// 1. dc 2, 3. 출력할 윈도우 left, top 좌표, 4. 출력할 문자열 5. 문자열 버퍼 크기
	
	//RECT rc{ 0, 0, 50, 50 };
	//DrawText(m_hDC, m_szFPS, lstrlen(m_szFPS), &rc, DT_RIGHT);
	// 1. dc 2. 출력할 문자열 3. 문자열 버퍼 크기 4. 출력할 렉트 주소, 5. 출력 옵션

	//TCHAR	szBuff[32] = L"";
	// 소수점 자리 출력이 불가능하다. winapi 라이브러리에서 제공하는 함수
	//wsprintf(szBuff, L"Bullet : %d", m_ObjList[OBJ_BULLET].size());

	// visual c++ 라이브러리에서 제공(모든 서식 문자를 지원)
	//swprintf_s(szBuff, L"Bullet : %f", 3.14f);
	//TextOut(m_hDC, 50, 50, szBuff, lstrlen(szBuff));
	
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

}

void CMainGame::Release(void)
{
	/*Safe_Delete<CObj*>(m_pPlayer);

	for (auto& iter : m_BulletList)
		Safe_Delete<CObj*>(iter);

	m_BulletList.clear();*/

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			Safe_Delete<CObj*>(iter);

		m_ObjList[i].clear();
	}

	ReleaseDC(g_hWnd, m_hDC);	
}

// 1. w,a,s,d 키를 눌러 4방향 총알쏘기
// 2. 가로 세로가 100씩 작은 렉트를 만들고 사각형 범위를 벗어나면 미사일을 삭제하라