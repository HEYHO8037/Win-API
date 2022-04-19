#include "stdafx.h"
#include "MainGame.h"


CMainGame::CMainGame()
	: m_pPlayer(nullptr)
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);

	if (!m_pPlayer)
	{
		m_pPlayer = new CPlayer;
		m_pPlayer->Initialize();
		dynamic_cast<CPlayer*>(m_pPlayer)->GetBulletList(&m_pBulletList);
	}

}

void CMainGame::Update(void)
{
	m_pPlayer->Update();

	list<CBullet*>::iterator iter;
	list<CBullet*>::iterator iterEnd = m_pBulletList.end();

	for (iter = m_pBulletList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Update();
	}
	
	ContactRect();

}

void CMainGame::Render(void)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	Rectangle(m_hDC, 100, 100, WINCX - 100, WINCY - 100);

	m_pPlayer->Render(m_hDC);

	list<CBullet*>::iterator iter;
	list<CBullet*>::iterator iterEnd = m_pBulletList.end();

	for (iter = m_pBulletList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Render(m_hDC);
	}
	
	
}

void CMainGame::Release(void)
{
	list<CBullet*>::iterator iter;
	list<CBullet*>::iterator iterEnd = m_pBulletList.end();

	for (iter = m_pBulletList.begin(); iter != iterEnd; ++iter)
	{
		delete (*iter);

		iter = m_pBulletList.erase(iter);
		iterEnd = m_pBulletList.end();
	}

	m_pBulletList.clear();

	Safe_Delete<CObj*>(m_pPlayer);

	ReleaseDC(g_hWnd, m_hDC);	
}

void CMainGame::ContactRect()
{
	list<CBullet*>::iterator iter;
	list<CBullet*>::iterator iterEnd = m_pBulletList.end();

	for (iter = m_pBulletList.begin(); iter != iterEnd; iter)
	{
		if ((*iter)->GetRect().bottom > WINCY - 100)
		{
			delete (*iter);
			iter = m_pBulletList.erase(iter);
			iterEnd = m_pBulletList.end();
		}
		else if ((*iter)->GetRect().top < 100)
		{
			delete (*iter);
			iter = m_pBulletList.erase(iter);
			iterEnd = m_pBulletList.end();
		}
		else if ((*iter)->GetRect().left < 100)
		{
			delete (*iter);
			iter = m_pBulletList.erase(iter);
			iterEnd = m_pBulletList.end();
		}
		else if ((*iter)->GetRect().right > WINCX - 100)
		{
			delete (*iter);
			iter = m_pBulletList.erase(iter);
			iterEnd = m_pBulletList.end();
		}
		else
		{
			++iter;
		}
	}
}


// 1. w,a,s,d 키를 눌러 4방향 총알쏘기
// 2. 가로 세로가 100씩 작은 렉트를 만들고 사각형 범위를 벗어나면 미사일을 삭제하라