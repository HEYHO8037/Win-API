#include "stdafx.h"
#include "MainGame.h"


CMainGame::CMainGame()
	: m_pPlayer(nullptr), m_pMonster(nullptr)
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
		dynamic_cast<CPlayer*>(m_pPlayer)->SetBulletList(&m_pBulletList);
	}

	if (!m_pMonster)
	{
		m_pMonster = new CMonster;
		m_pMonster->Initialize();
	}

}

void CMainGame::Update(void)
{
	m_pPlayer->Update();

	if (m_pMonster)
	{
		m_pMonster->Update();
	}

	list<CBullet*>::iterator iter;
	list<CBullet*>::iterator iterEnd = m_pBulletList.end();

	for (iter = m_pBulletList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Update();
	}
}

void CMainGame::Late_Update(void)
{
	ContactRect();
	ContactMonster();
}

void CMainGame::Render(void)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	Rectangle(m_hDC, 100, 100, WINCX - 100, WINCY - 100);

	m_pPlayer->Render(m_hDC);

	if (m_pMonster)
	{
		m_pMonster->Render(m_hDC);
	}

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
	Safe_Delete<CObj*>(m_pMonster);

	ReleaseDC(g_hWnd, m_hDC);	
}

void CMainGame::ContactRect()
{
	list<CBullet*>::iterator iter;
	list<CBullet*>::iterator iterEnd = m_pBulletList.end();

	for (iter = m_pBulletList.begin(); iter != iterEnd; iter)
	{
		if ((*iter)->GetRect().bottom >= WINCY - 100)
		{
			delete (*iter);
			iter = m_pBulletList.erase(iter);
			iterEnd = m_pBulletList.end();
		}
		else if ((*iter)->GetRect().top <= 100)
		{
			delete (*iter);
			iter = m_pBulletList.erase(iter);
			iterEnd = m_pBulletList.end();
		}
		else if ((*iter)->GetRect().left <= 100)
		{
			delete (*iter);
			iter = m_pBulletList.erase(iter);
			iterEnd = m_pBulletList.end();
		}
		else if ((*iter)->GetRect().right >= WINCX - 100)
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

void CMainGame::ContactMonster()
{
	if (!m_pMonster)
	{
		return;
	}

	list<CBullet*>::iterator iter;
	list<CBullet*>::iterator iterEnd = m_pBulletList.end();
	RECT rc{};

	for (iter = m_pBulletList.begin(); iter != iterEnd; iter)
	{
		if (IntersectRect(&rc, &dynamic_cast<CMonster*>(m_pMonster)->GetRect(), &(*iter)->GetRect()))
		{
			delete (*iter);
			iter = m_pBulletList.erase(iter);
			Safe_Delete<CObj*>(m_pMonster);
			break;
		}
		else
		{
			++iter;
		}
	}

}


// 1. w,a,s,d 키를 눌러 4방향 총알쏘기
// 2. 가로 세로가 100씩 작은 렉트를 만들고 사각형 범위를 벗어나면 미사일을 삭제하라
// 3. 몬스터를 생성하여 작은 사각형 안에서 벽에 부딪히면 반대 방향으로 움직이도록 만들기.(최초는 오른쪽으로 이동)
// 4. 총알에 부딪히면 몬스터를 제거를 하면 된다.(IntersectRect 함수를 사용하라)
// InterSectRect 1. 두박스를 충돌하면서 발생한 렉트의 정보를 저장할 Rect의 주소값
// 2. 첫번째 충돌 RECT 주소값
// 3. 두번째 충돌 RECT 주소값

// 5. 피타고라스 정리 한번 봐라.

// 1. 삼각함수 공부하기
// 2. 플레이어 포신 추가하고 회전을 시켜라
// 3. 포신방향으로 플레이어를 이동해라.(삼각함수)